//
// Created by utente on 03/11/2019.
//

#include <iostream>
#include <utility>
#include <QtCore/QDataStream>
#include <QtCore/QBuffer>
#include <QtSql/QSqlDatabase>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include "ServerThread.h"
#include "NetworkServer.h"
#include "Packet/LoginInfo.h"


SocketsPool ServerThread::_sockets;

ServerThread::ServerThread(qintptr socketDesc, MessageHandler *msgHandler,QObject *parent):QThread(parent){
    this->socketDescriptor = socketDesc;
    this->msgHandler = std::shared_ptr<MessageHandler>(msgHandler);
    this->_username = "";
    this->_siteID = -1;
    this->operatingFileName = "";
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
    //std::cout << "Thread " << std::this_thread::get_id() << " reading from socket " << this->socketDescriptor<< std::endl;
    QDataStream in;
    qint32 bytes=0;
    qint32 source=0;
    quint32 errcode;
    quint32 type_of_data;

    //qDebug() << "Receving packet";

    in.setDevice(this->socket.get());
    in.setVersion(QDataStream::Qt_5_5);

    while(this->socket->bytesAvailable()>0) {

        std::cout<<"--starting number of Available  Bytes: "<<socket->bytesAvailable()<<std::endl;
        if(this->socketSize==0) {
            in >> bytes;
            this->socketSize = bytes;
        }
        if(this->socketSize!=0 && bytes!=-14){
            if(socket->bytesAvailable()!=this->socketSize-4){
                return;
            }
        }

        in >> source>>errcode >> type_of_data;

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
                sendMessage(packet);
            }
            break;
        }
        std::cout<<"--ending number of Available Bytes: "<<socket->bytesAvailable()<<std::endl;
        std::cout<<std::endl;
        this->socketSize=0;
    }
    std::cout<<"ending number of Available Bytes: "<<socket->bytesAvailable()<<std::endl;

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

            _siteID = packet.getPayload()->getSiteId();
            QPointer<QThread> th(this);
            qRegisterMetaType<QPointer<QThread>>("QPointer<QThread>");
            emit recordThread(th);

            /// in mancanza di un client che mi chieda di ricevere un file, faccio questo nella
            /// procedura di login
                QString name = QString::fromStdString("/prova"+std::to_string(_siteID)+">F");
                std::cout << name.toStdString() << std::endl;
                QVector<QString> vec = {name};
                auto comm = std::make_shared<Command>(_siteID, Command::opn, vec);

                QString fileName = comm->opnCommand(threadId, _username);
                if (!fileName.isEmpty()) {
                    operatingFileName = fileName;
                    std::cout << fileName.toStdString() << std::endl;
                }
                else
                    std::cout << "opn command failed!" << std::endl;

                vec.clear();
                vec.insert(0, fileName);
                comm->setArgs(vec);
                _sockets.attachSocket(fileName,_siteID,socket.get());
                msgHandler->submit(&NetworkServer::processOpnCommand, comm);
            /// quando il client chiederà autonomamente di aprire un file
            /// ELIMINARE FINO A QUI

        } else {
            std::cout << "client not logged!" << std::endl;
            sendPacket(packet);
        }
    }
}



void ServerThread::recvMessage(DataPacket& packet,QDataStream& in){
    qint32 siteId;
    QString formattedMessages;


    in.setDevice(socket.get());
    in.setVersion(QDataStream::Qt_5_5);

    in >> siteId  >> formattedMessages;

    auto *strMess = new StringMessages(formattedMessages,siteId);
    packet.setPayload(std::shared_ptr<StringMessages>(strMess));

    //se l'utente non è loggato non deve poter inviare pacchetti con dentro Message
    //però potrebbe e in questo caso l'unico modo per pulire il socket è leggerlo
    if(!_username.isEmpty()) {

        for (auto msg: strMess->stringToMessages()) {

            std::shared_ptr<Message> m = std::make_shared<Message>(msg);
            if (msg.getAction() == Message::insertion) {
                msgHandler->submit(NetworkServer::localInsert, m);
            } else {
                msgHandler->submit(NetworkServer::localErase, m);
            }
        }
        _sockets.broadcast(operatingFileName,_siteID,packet);
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
            if(!fileName.isEmpty()) {
                operatingFileName = fileName;
                _sockets.attachSocket(fileName,_siteID,socket.get());
                std::cout << fileName.toStdString() << std::endl;
                QVector<QString> vec = {fileName};
                command->setArgs(vec);
                msgHandler->submit(&NetworkServer::processOpnCommand, command);
            }else
                std::cout << "opn command failed!" << std::endl;
            break;
        }

        case (Command::cls):{
            if( operatingFileName!="")
                _sockets.detachSocket(operatingFileName,_siteID);
            break;
        }

        default:
            std::cout << "Coglione errore nel Command" << std::endl;
    }
}

void ServerThread::sendPacket(DataPacket packet){

    std::cout<<"thread "<<std::this_thread::get_id()<<" sending packet to "<<this->socketDescriptor<<std::endl;

    switch(packet.getTypeOfData()){
        case (DataPacket::login): {
           sendLoginInfo(packet);
           break;
        }

        case (DataPacket::textTyping): {
            sendMessage(packet);
            break;
        }

        case (DataPacket::command): {
            sendCommand(packet);
            break;
        }

        default: {
            std::cout<<"Coglione c'è un errore"<<std::endl;
        }
    }
}

void ServerThread::sendLoginInfo(DataPacket &packet) {
    auto ptr = std::dynamic_pointer_cast<LoginInfo>(packet.getPayload());
    QDataStream out;
    out.setDevice(socket.get());
    out.setVersion(QDataStream::Qt_5_5);

    qint32 bytes=-14;//TODO dimensione socket
    out << bytes<<packet.getSource() << packet.getErrcode() << packet.getTypeOfData();
    out << ptr->getSiteId() << ptr->getType() << ptr->getUser() << ptr->getPassword();
    socket->waitForBytesWritten(-1);
}

void ServerThread::sendMessage(DataPacket& packet){

    QDataStream out;
    out.setDevice(socket.get());
    out.setVersion(QDataStream::Qt_5_5);

    auto strMess = std::dynamic_pointer_cast<StringMessages>(packet.getPayload());

    qint32 bytes=16+(strMess->getFormattedMessages().size()*16)/8+4+4;
        out << bytes<<packet.getSource() << packet.getErrcode() << packet.getTypeOfData() <<
        strMess->getSiteId() << strMess->getFormattedMessages();
    socket->waitForBytesWritten(-1);

}

void ServerThread::sendCommand(DataPacket& packet){
    QDataStream out;
    out.setDevice(socket.get());
    out.setVersion(QDataStream::Qt_5_5);

    auto ptr = std::dynamic_pointer_cast<Command>(packet.getPayload());
    qint32 bytes=-14;//TODO dimensione socket
    out << bytes<<packet.getSource() << packet.getErrcode() << packet.getTypeOfData();
    out << ptr->getSiteId() << (quint32) ptr->getCmd() << ptr->getArgs();
}


void ServerThread::disconnected()
{

    if( operatingFileName!="")
        _sockets.detachSocket(operatingFileName,_siteID);

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
