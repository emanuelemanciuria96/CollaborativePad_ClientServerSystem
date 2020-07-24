//
// Created by utente on 03/11/2019.
//

#include <iostream>
#include <utility>
#include <QtCore/QDataStream>
#include <fstream>
#include <QtCore/QBuffer>
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
    this->isLogged = false;
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
    std::cout << "recvLoginInfo: " << user.toStdString() << " " << password.toStdString() << std::endl;
    if(type == LoginInfo::login_request && !isLogged) {
        auto shr = std::make_shared<LoginInfo>( -1, type, user, password);
        packet.setPayload(shr);
        if (shr.get()->login() != -1) {
            std::cout << "client successfully logged!" << std::endl;
            isLogged = true;                                               //ATTUALMENTE se l'utente cerca di loggarsi ma è già loggato, il server
            sendPacket(packet);                           //non fa nulla, non risponde con messaggi di errore

            {
                std::lock_guard lg(skt_mutex);
                _sockets.insert(std::make_pair(this->socket.get(),new std::mutex()));
            }

            _siteID = packet.getPayload()->getSiteId();
            QPointer<QThread> th(this);
            qRegisterMetaType<QPointer<QThread>>("QPointer<QThread>");
            emit recordThread(th);

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

        strMess.get()->push(*msg);
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
    quint32 cmd;
    QString arg1;
    QString arg2;

    in >> siteId >> cmd >> arg1 >> arg2;
    packet.setPayload( std::make_shared<Command>(siteId,(Command::cmd_t)cmd,arg1,arg2));

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

    {
        std::lock_guard lg(*mtx);
        std::cout<<"Bytes written: "<<buf.data().size()<<std::endl;
        out.device()->write(buf.data());
        socket->waitForBytesWritten(-1);
    }

}

void ServerThread::saveFileJson(std::string dir,std::vector<Symbol> _symbols){//vector<symbol> to json
    std::ofstream file_id;
    file_id.open(dir);
    Json::Value event;
    int index=0;
    for(auto itr:_symbols) {
        event[index]["index"] = index;
        event[index]["char"] = QString(itr.getValue()).toStdString();
        event[index]["symId"]["siteId"] = itr.getSymId().getSiteId();
        event[index]["symId"]["count"] = itr.getSymId().getCount();

        Json::Value vec(Json::arrayValue);

        for(int i=0; i<itr.getPos().size();i++){
            vec.append(Json::Value(itr.getPos()[i]));
        }
        event[index]["pos"]=vec;

        index++;
    }

    Json::StyledWriter styledWriter;
    file_id << styledWriter.write(event);

    file_id.close();
}

std::vector<Symbol> ServerThread::loadFileJson(std::string dir){//json to vector<symbol>
    std::ifstream file_input(dir);
    Json::Reader reader;
    Json::Value root;
    reader.parse(file_input, root);

    std::vector<Symbol> _symbols;

    for(int i=0; i<root.size(); i++) {
        QChar value=*(root[i]["char"].asCString());
        qint32 _siteId=root[i]["symId"]["siteId"].asUInt64();
        qint32 _counter=root[i]["symId"]["count"].asUInt64();
        std::vector<quint32> pos;
        Symbol s(value,_siteId,_counter, pos);
        for(int j=0;j<root[i]["pos"].size();j++){
            qint32 val=root[i]["pos"][j].asUInt64();
            pos.push_back(val);
        }
        _symbols.insert(_symbols.end(),s);
    }
    return _symbols;
}

void ServerThread::disconnected()
{

    std::shared_lock sl(skt_mutex);
    auto i = _sockets.find(socket.get());
    sl.unlock();
    std::lock_guard lg(skt_mutex);
    _sockets.erase(i);

    socket->deleteLater();
    std::cout<<"Client disconnected!"<<std::endl;
    exit(0);
}

