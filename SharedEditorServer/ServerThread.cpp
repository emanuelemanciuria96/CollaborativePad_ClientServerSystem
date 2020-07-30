//
// Created by utente on 03/11/2019.
//

#include <iostream>
#include <utility>
#include <QtCore/QDataStream>
#include <fstream>
#include <QtCore/QBuffer>
#include <QtSql/QSqlDatabase>
#include <QtCore/QFile>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include "ServerThread.h"
#include "NetworkServer.h"
#include "Packet/LoginInfo.h"
#include "json/json.h"

std::shared_mutex ServerThread::skt_mutex;  // questo è lo shared mutex per la struttura "_sockets"
std::map<Socket*,std::mutex*> ServerThread::_sockets; //qui ci sono dei mutex esclisivi per ogni socket
/// PER ORA USO IL VETTORE PER TESTARE IL FUNZIONAMENTO, POI INSERIRO' LA MAPPA (IL VETTORE SO USARLO BENE, LA MAPPA ANCORA NO)

ServerThread::ServerThread(qintptr socketDesc, MessageHandler *msgHandler,QObject *parent):QThread(parent){
    this->socketDescriptor = socketDesc;
    this->msgHandler = std::shared_ptr<MessageHandler>(msgHandler);
    this->_username = "";
    this->_siteID = -1;
}

void ServerThread::run()
{

    std::cout<<"ServerThread::run line 27, thread "<<std::this_thread::get_id()<<std::endl;

    socket = std::shared_ptr<Socket>(new Socket());
    socket->moveToThread(this);

    if ( !socket->setSocketDescriptor(this->socketDescriptor) )   //setto il descriptor del socket
    {
        emit error (socket->error());       //da gestire
        return;
    }

    connect(socket.get(),&Socket::sendMessage,this,&ServerThread::sendPacket,Qt::QueuedConnection);
    connect(socket.get(), SIGNAL(readyRead()), this, SLOT(recvPacket()), Qt::DirectConnection);
    connect(socket.get(), SIGNAL(disconnected()), this, SLOT(disconnected()));

    setThreadId();
    QSqlDatabase::addDatabase("QSQLITE", threadId+"_login");
    QSqlDatabase::addDatabase("QSQLITE", threadId+"_directories");
    QSqlDatabase::addDatabase("QSQLITE", threadId+"_files");

    exec(); //loop degli eventi attivato qui
}


void ServerThread::recvPacket() {
    std::cout << "Thread " << std::this_thread::get_id() << " reading from socket " << this->socketDescriptor
              << std::endl;

    QDataStream in;
    qint32 source;
    quint32 errcode;
    quint32 type_of_data;

    qDebug() << "Receving packet";

    in.setDevice(this->socket.get());
    in.setVersion(QDataStream::Qt_5_5);

    while(this->socket->bytesAvailable()>0) {
        std::cout<<"starting number of Available  Bytes: "<<socket->bytesAvailable()<<std::endl;
        in >> source >> errcode >> type_of_data;
        DataPacket packet(source, errcode, (DataPacket::data_t) type_of_data);

        switch (type_of_data) {
            case (DataPacket::login): {
                recvLoginInfo(packet, in);
                break;
            }

            case (DataPacket::textTyping): {
                recvMessage(packet, in);
                break;
            }

            case (DataPacket::command): {
                recvCommand(packet, in);
                break;
            }

            default: {
                std::cout << "il dato in arrivo è corrotto, necessario un riallineamento dei dati" << std::endl;
                packet.setErrcode(-1);
                packet.setSource(-1);
                packet.setTypeOfData(DataPacket::textTyping);
                packet.setPayload(std::make_shared<StringMessages>());

                socket->readAll();
                std::shared_lock sl(skt_mutex);
                for (auto skt: _sockets) {
                    if (skt.first == socket.get() ) {
                        sl.unlock();
                        sendMessage(packet,skt.second);
                        sl.lock();
                    }
                }
                break;
            }
        }
        std::cout<<"ending number of Available Bytes: "<<socket->bytesAvailable()<<std::endl;
    }

}

void ServerThread::recvLoginInfo(DataPacket& packet, QDataStream& in) {
    quint32 siteId;
    qint32 type;
    QString user;
    QString password;

    in >> siteId >> type >> user >> password;

    if(type == LoginInfo::login_request && _username.isEmpty()) {
        auto shr = std::make_shared<LoginInfo>( -1, (LoginInfo::type_t)type, user, password);
        packet.setPayload(shr);
        _siteID = shr->login(threadId);
        if (_siteID != -1) {
            _username = user;
            std::cout << "client "+user.toStdString()+" successfully logged!" << std::endl;        //ATTUALMENTE se l'utente cerca di loggarsi ma è già loggato, il server
            sendPacket(packet);                                                                   //non fa nulla, non risponde con messaggi di errore

            {
                std::lock_guard lg(skt_mutex);
                _sockets.insert(std::make_pair(this->socket.get(),new std::mutex()));
            }

            _siteID = packet.getPayload()->getSiteId();
            QPointer<QThread> th(this);
            qRegisterMetaType<QPointer<QThread>>("QPointer<QThread>");
            emit recordThread(th);

            /// in mancanza di un client che mi chieda di ricevere un file, faccio questo nella
            /// procedura di login
            QVector<QString> vec = {"/prova>F"};
            auto comm = std::make_shared<Command>(_siteID,Command::opn,vec);
            QString fileName;

            fileName = comm->opnCommand(threadId, _username);
            if(!fileName.isEmpty())
                std::cout << fileName.toStdString() << std::endl;
            else
                std::cout << "opn command failed!" << std::endl;

            vec.clear();
            vec.insert(0,fileName);
            comm->setArgs(vec);

            msgHandler->submit(&NetworkServer::processOpnCommand,comm);

        } else {
            std::cout << "client not logged!" << std::endl;
            sendPacket(packet);
        }
    }
}


void ServerThread::recvMessage(DataPacket& packet,QDataStream& in){
    qint32 siteID;
    quint32 action;
    quint32 localIndex;
    qint32 siteIDs;
    quint32 count;
    QChar ch;
    quint32 posDim;
    std::vector<quint32> pos;

    std::shared_ptr<StringMessages> strMess(new StringMessages(packet.getSource()));

    in.setDevice(socket.get());
    while(socket->bytesAvailable()>0){
        pos.clear();
        in>>siteID>>action>>localIndex>>siteIDs>>count>>ch>>posDim;
        for(quint32 i=0;i<posDim;i++){
            quint32 p;
            in>>p;
            pos.push_back(p);
        }
        Symbol sym(ch,siteIDs,count,pos);
        auto msg = std::make_shared<Message>((Message::action_t)action,siteID,sym,localIndex);
        if (action == Message::insertion) {
            msgHandler->submit(NetworkServer::localInsert, msg);
        } else {
            msgHandler->submit(NetworkServer::localErase, msg);
        }

        strMess->push(*msg);
    }
    packet.setPayload(strMess);

    std::shared_lock sl(skt_mutex);
    for (auto skt: _sockets) {
        sl.unlock();
        if (skt.first != socket.get()) {
            int id = qMetaTypeId<DataPacket>();
            emit skt.first->sendMessage(packet,skt.second);
        }
        sl.lock();
    }

}


void ServerThread::recvCommand(DataPacket &packet, QDataStream &in) {
    qint32 siteId;
    qint32 cmd;
    QVector<QString> args;

    in >> siteId >> cmd >> args;
    packet.setPayload(std::make_shared<Command>(siteId,(Command::cmd_t)cmd,std::move(args)));
    auto command = std::dynamic_pointer_cast<Command>(packet.getPayload());

    switch(cmd){
        case (Command::cd):{
            command->cdCommand(threadId, _username);
            sendPacket(packet);
            break;
        }

        case (Command::mkdir):{
            if(command->mkdirCommand(threadId, _username))
                std::cout << "mkdir command ok!" << std::endl;
            else
                std::cout << "mkdir command failed!" << std::endl;
            break;
        }

        case (Command::rm):{
            if(command->rmCommand(threadId, _username))
                std::cout << "rm command ok!" << std::endl;
            else
                std::cout << "mkdir command failed!" << std::endl;
            break;
        }

        case (Command::cp):{
            break;
        }

        case (Command::mv):{
            break;
        }

        case (Command::opn):{
            QString fileName;

            fileName = command->opnCommand(threadId, _username);
            if(!fileName.isEmpty())
                std::cout << fileName.toStdString() << std::endl;
            else
                std::cout << "opn command failed!" << std::endl;
            break;
        }

        case (Command::cls):{
            break;
        }

        default:
            std::cout << "Coglione errore nel Command" << std::endl;
    }
}

void ServerThread::sendPacket(DataPacket packet, std::mutex *mtx){

    std::cout<<"thread "<<std::this_thread::get_id()<<" sending packet to "<<this->socketDescriptor<<std::endl;

    switch(packet.getTypeOfData()){
        case (DataPacket::login): {
           sendLoginInfo(packet,mtx);
           break;
        }

        case (DataPacket::textTyping): {
            sendMessage(packet, mtx);
            break;
        }

        case (DataPacket::command): {
            sendCommand(packet, mtx);
            break;
        }

        default: {
            std::cout<<"Coglione c'è un errore"<<std::endl;
        }
    }
}

void ServerThread::sendLoginInfo(DataPacket &packet, std::mutex *mtx) {
    auto ptr = std::dynamic_pointer_cast<LoginInfo>(packet.getPayload());
    QDataStream out;
    out.setDevice(socket.get());
    out.setVersion(QDataStream::Qt_5_5);

    out << packet.getSource() << packet.getErrcode() << packet.getTypeOfData();
    out << ptr->getSiteId() << ptr->getType() << ptr->getUser() << ptr->getPassword();
    socket->waitForBytesWritten(-1);
}

void ServerThread::sendMessage(DataPacket& packet,std::mutex* mtx){

    QBuffer buf;
    buf.open(QBuffer::WriteOnly);
    QDataStream tmp(&buf);
    QDataStream out;
    out.setDevice(socket.get());
    out.setVersion(QDataStream::Qt_5_5);

    auto msgs = std::dynamic_pointer_cast<StringMessages>(packet.getPayload());
    tmp << packet.getSource() << packet.getErrcode() << (quint32)packet.getTypeOfData();

    while(!msgs->getMessages().get()->empty()){
        Message m = msgs->pop();
        Symbol s = m.getSymbol();
        quint32 posDim = s.getPos().size();
        tmp<<m.getSiteId()<<(quint32)m.getAction()<<m.getLocalIndex()
           <<s.getSymId().getSiteId()<<s.getSymId().getCount()
           <<s.getValue()<<posDim;
        for(auto p:s.getPos())
            tmp<<p;

    }

    if(mtx != nullptr){
        std::lock_guard lg(*mtx);
        std::cout<<"Bytes written: "<<buf.data().size()<<std::endl;
        out.device()->write(buf.data());
        socket->waitForBytesWritten(-1);
    }
    else{
        std::cout<<"Bytes written: "<<buf.data().size()<<std::endl;
        out.device()->write(buf.data());
        socket->waitForBytesWritten(-1);
    }

}

void ServerThread::sendCommand(DataPacket& packet, std::mutex *mtx){
    QDataStream out;
    out.setDevice(socket.get());
    out.setVersion(QDataStream::Qt_5_5);

    auto ptr = std::dynamic_pointer_cast<Command>(packet.getPayload());
    out << packet.getSource() << packet.getErrcode() << packet.getTypeOfData();
    out << ptr->getSiteId() << (quint32) ptr->getCmd() << ptr->getArgs();
}


void ServerThread::disconnected()
{

    std::shared_lock sl(skt_mutex);
    auto i = _sockets.find(socket.get());
    sl.unlock();
    std::lock_guard lg(skt_mutex);

    if( i != _sockets.end() )
        _sockets.erase(i);

    socket->deleteLater();
    QSqlDatabase::removeDatabase(threadId+"_login");
    QSqlDatabase::removeDatabase(threadId+"_directories");
    QSqlDatabase::removeDatabase(threadId+"_files");
    std::cout<<"Client disconnected!"<<std::endl;
    exit(0);
}

void ServerThread::setThreadId() {
    auto myid = std::this_thread::get_id();
    std::stringstream ss;
    ss << myid;
    std::string IdString = ss.str();
    threadId = QString::fromStdString(IdString);
}