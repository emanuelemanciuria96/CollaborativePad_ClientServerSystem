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


std::shared_mutex ServerThread::db_op_mtx;
SocketsPool ServerThread::_sockets;
qint32 fixedBytesWritten = sizeof(qint32)+sizeof(qint32)+sizeof(quint32)+sizeof(quint32)+sizeof(qint32);
///                                bytes     source        errcode      DataPacket::data_t   siteID



ServerThread::ServerThread(qintptr socketDesc, std::shared_ptr<MessageHandler> msgHandler,QObject *parent):QThread(parent){
    this->socketDescriptor = socketDesc;
    this->msgHandler = msgHandler;
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
    connect(socket.get(),&Socket::sendFile,this,&ServerThread::sendFile,Qt::QueuedConnection);
    connect(socket.get(),&Socket::sendPendentDelete,this,&ServerThread::sendPendentDelete,Qt::QueuedConnection);
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

        // std::cout<<"--starting number of Available  Bytes: "<<socket->bytesAvailable()<<std::endl;
        if(this->socketSize==0) {
            in >> bytes;
            this->socketSize = bytes;
        }
        if(this->socketSize!=0 && bytes!=-14){
            if(socket->bytesAvailable()<this->socketSize-4){
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

            case (DataPacket::cursorPos): {
                recvCursorPos(packet, in);
                break;
            }

            default: {
                std::cout << "il dato in arrivo è corrotto, necessario un riallineamento dei dati" << std::endl;
                packet.setErrcode(-1);
                packet.setSource(-1);
                packet.setTypeOfData(DataPacket::textTyping);
                packet.setPayload(std::make_shared<StringMessages>(_siteID));

                socket->readAll();
                sendMessage(packet);
            }
                break;
        }
        // std::cout<<"--ending number of Available Bytes: "<<socket->bytesAvailable()<<std::endl;
        this->socketSize=0;
    }
    // std::cout<<"ending number of Available Bytes: "<<socket->bytesAvailable()<<std::endl;

}



void ServerThread::recvLoginInfo(DataPacket& packet, QDataStream& in) {
    quint32 siteId;
    qint32 type;
    QString user;
    QString password;
    QPixmap image;
    QString name;
    QString email;

    in >> siteId >> type >> user >> password >> name >> image >> email;

    switch (type) {
        case LoginInfo::login_request:
            if(_username.isEmpty()) {
                auto shr = std::make_shared<LoginInfo>( -1, (LoginInfo::type_t)type, user, password);
                packet.setPayload(shr);

                try {
                    if (shr->login(threadId)) {
                        _siteID = shr->getSiteId();
                        _username = user;

                        QPointer<QThread> th(this);
                        qRegisterMetaType<QPointer<QThread>>("QPointer<QThread>");
                        emit recordThread(th);

                        std::cout << "client " + user.toStdString() + " successfully logged!"
                                  << std::endl;        //ATTUALMENTE se l'utente cerca di loggarsi ma è già loggato, il server
                        sendPacket(packet);            //non fa nulla, non risponde con messaggi di errore

                        DataPacket pkt(0, 0, DataPacket::command, std::make_shared<Command>(_siteID, Command::ls, QVector<QString>{}) );
                        {
                            std::shared_lock sl(db_op_mtx);
                            std::static_pointer_cast<Command>(pkt.getPayload())->lsCommand(threadId);
                            _sockets.recordSocket(_siteID, socket);
                        }
                        sendPacket(pkt);

                        DataPacket cmdPacket(_siteID, 0, DataPacket::command);
                        auto cmdPayload = std::make_shared<Command>(_siteID, Command::lsInvite, QVector<QString>());
                        cmdPacket.setPayload(cmdPayload);
                        cmdPayload->lsInviteCommand(threadId);
                        sendPacket(cmdPacket);

                    } else {
                        std::cout << "client not logged!" << std::endl;
                        sendPacket(packet);
                    }
                }catch( LoginException e ){
                    std::cout<<e.what()<<endl;

                    _username = "";
                    _siteID = -1;
                    shr->setSiteId(_siteID);
                    shr->setType(LoginInfo::login_alconn_error);
                    sendPacket(packet);
                }

            }
            break;

        case LoginInfo::update_info:
            if (!_username.isEmpty()) {
                auto shr = std::make_shared<LoginInfo>( _siteID, (LoginInfo::type_t)type, "", "");
                shr->setImage(image);
                shr->setName(name);
                shr->setEmail(email);
                shr->updateInfo(threadId);
            }
            break;

        case LoginInfo::signup_request:
            if(_username.isEmpty()){
                auto shr = std::make_shared<LoginInfo>( -1, (LoginInfo::type_t)type, user, password);
                shr->setImage(image);
                shr->setName(name);
                shr->setEmail(email);
                packet.setPayload(shr);
                if (shr->signup(threadId)) {
                    _siteID = shr->getSiteId();
                    _username = user;
                    std::cout << "client "+user.toStdString()+" successfully signed up!" << std::endl;        //ATTUALMENTE se l'utente cerca di loggarsi ma è già loggato, il server
                    sendPacket(packet);                                                                   //non fa nulla, non risponde con messaggi di errore

                    DataPacket pkt(0, 0, DataPacket::command,  std::make_shared<Command>(_siteID, Command::ls, QVector<QString>{}) );
                    {
                        std::shared_lock sl(db_op_mtx);
                        std::static_pointer_cast<Command>(pkt.getPayload())->lsCommand(threadId);
                        _sockets.recordSocket(_siteID, socket);
                    }
                    sendPacket(pkt);

                    QPointer<QThread> th(this);
                    qRegisterMetaType<QPointer<QThread>>("QPointer<QThread>");
                    emit recordThread(th);

                } else {
                    std::cout << "client not signed up!" << std::endl;
                    sendPacket(packet);
                }
            }
            break;

        case LoginInfo::search_user_request:
            if(!_username.isEmpty()) {
                auto shr = std::make_shared<LoginInfo>(siteId, (LoginInfo::type_t) type, user);
                packet.setPayload(shr);
                shr->searchUser(threadId);
                sendPacket(packet);
            }
            break;

        default:
            std::cout << "errore nella recvlogininfo" << std::endl;
            break;

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

    // std::cout<<" --- number of arrived messages at once "<<strMess->stringToMessages().size()<<std::endl;

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
        case (Command::ren):{
            std::unique_lock ul(db_op_mtx);
            auto listId = command->renCommand(threadId);
            if( !listId.empty() ) {
                _sockets.broadcast(listId,packet);
                ul.unlock();
            }
            else
                std::cout << "rename command isn't broadcasted" << std::endl;
            break;
        }

        case (Command::rm):{
            auto owner = command->getArgs().first().split("/").first();
            if(owner != _username) {
                std::unique_lock ul(db_op_mtx);
                if (command->rmCommand(threadId))
                    ul.unlock();
                else
                    std::cout << "rm command failed!" << std::endl;
            }
            else{
                std::unique_lock ul(db_op_mtx);
                auto listId = command->rmAllCommand(threadId);
                if (!listId.empty()) {
                    msgHandler->submit(NetworkServer::processRmCommand,std::make_shared<Command>(*command));
                    pendentDeleteList.insert(std::make_pair(command->getArgs().first(),std::move(listId)));
                    ul.unlock();
                }
                else
                    std::cout << "rm command failed!" << std::endl;
            }
            break;
        }

        case (Command::sv):{
            command->svCommand(threadId);
            break;
        }

        case (Command::opn):{
            std::shared_lock sl(db_op_mtx);

            if( command->srcCommand(threadId) ) {
                QString fileName = command->getArgs().front();
                _sockets.attachSocket(fileName,_siteID,socket);
                std::cout << fileName.toStdString() << std::endl;
                msgHandler->submit(&NetworkServer::processOpnCommand, command);
                sl.unlock();

                operatingFileName = fileName;

            }else
                std::cout << "opn command failed!" << std::endl;

            break;
        }

        case (Command::cls):{
            DataPacket pkt(_siteID, 0, DataPacket::cursorPos);
            auto symbol = Symbol();
            pkt.setPayload(std::make_shared<CursorPosition>(symbol,-1,_siteID));

            if( operatingFileName!="" ) {
                _sockets.detachSocket(operatingFileName, _siteID);
                msgHandler->submit(&NetworkServer::processClsCommand, command);
                _sockets.broadcast(operatingFileName,_siteID,pkt);
                operatingFileName = "";

            }else
                std::cout << "cls command failed! Maybe the file has been deleted" << std::endl;

            break;
        }

        case (Command::ls):{
            std::shared_lock sl(db_op_mtx);
            command->lsCommand(threadId);
            sendPacket(packet);
            break;
        }

        case (Command::invite):{
            std::unique_lock ul(db_op_mtx);
            command->inviteCommand(threadId);
            sendPacket(packet);
            if (command->getArgs().first() == "ok") {
                auto userSiteID = command->getArgs().last().toInt();
                DataPacket invitePacket(userSiteID, 0, DataPacket::command);
                auto payload = std::make_shared<Command>(userSiteID, Command::lsInvite, QVector<QString>());
                payload->lsInviteCommand(threadId);
                invitePacket.setPayload(payload);
                QVector<qint32> vector(1, userSiteID);
                _sockets.broadcast(vector, invitePacket);
            }
            break;
        }

        case (Command::ctrlInvite): {
            std::unique_lock ul(db_op_mtx);
            command->ctrlInviteCommand(threadId);
            break;
        }

        case (Command::uri): {
            std::unique_lock ul(db_op_mtx);
            command->uriCommand(threadId);
            sendPacket(packet);
            if (command->getArgs().first() == "invite-existing") {
                DataPacket invitePacket(_siteID, 0, DataPacket::command);
                auto payload = std::make_shared<Command>(_siteID, Command::lsInvite, QVector<QString>());
                payload->lsInviteCommand(threadId);
                invitePacket.setPayload(payload);
                QVector<qint32> vector(1, _siteID);
                _sockets.broadcast(vector, invitePacket);
            }
            break;
        }

        case (Command::fsName): {
            std::unique_lock ul(db_op_mtx);
            command->fsNameCommand(threadId);
            sendPacket(packet);
            break;
        }

        default:
            std::cout << "Coglione errore nel Command" << std::endl;
    }
}

void ServerThread::recvCursorPos(DataPacket &packet, QDataStream &in) {
    qint32 siteId;
    qint32 index;
    QChar ch;
    qint32 symbol_siteId;
    qint32 count;
    QVector<quint32> pos;

    in >> ch >> symbol_siteId >> count >> pos >> index >> siteId;

    //std::cout << "Dentro recv " << siteId << " pos:" << index << std::endl;

    auto pos_std = pos.toStdVector();
    auto symbol = Symbol(ch,symbol_siteId,count,pos_std);

    packet.setPayload(std::make_shared<CursorPosition>(symbol,index,siteId));

    _sockets.broadcast(operatingFileName, siteId,packet);
}

void ServerThread::sendPacket(DataPacket packet){

    //std::cout<<"thread "<<std::this_thread::get_id()<<" sending packet to "<<this->socketDescriptor<<std::endl;

    switch(packet.getTypeOfData()){
        case (DataPacket::login): {
            std::cout<<"thread "<<std::this_thread::get_id()<<" sending login info to client: "<<_username.toStdString()<<std::endl;
            sendLoginInfo(packet);
            break;
        }

        case (DataPacket::textTyping): {
            std::cout<<"thread "<<std::this_thread::get_id()<<" sending messages to client: "<<_username.toStdString()<<std::endl;
            sendMessage(packet);
            break;
        }

        case (DataPacket::command): {
            std::cout<<"thread "<<std::this_thread::get_id()<<" sending command to client: "<<_username.toStdString()<<std::endl;
            sendCommand(packet);
            break;
        }

        case (DataPacket::file_info):{
            std::cout<<"thread "<<std::this_thread::get_id()<<" sending file info to client: "<<_username.toStdString()<<std::endl;
            sendFileInfo(packet);
            break;
        }

        case (DataPacket::cursorPos): {
            sendCursorPos(packet);
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

    QBuffer buf;
    buf.open(QBuffer::WriteOnly);
    QDataStream tmp(&buf);
    tmp<<(quint32) ptr->getType() << ptr->getUser() << ptr->getPassword() << ptr->getName() << ptr->getImage() << ptr->getEmail();

    qint32 bytes = fixedBytesWritten + buf.data().size();

    out << bytes<<packet.getSource() << packet.getErrcode() << (quint32) packet.getTypeOfData();
    out << ptr->getSiteId() << (quint32) ptr->getType() << ptr->getUser() << ptr->getPassword() << ptr->getName() << ptr->getImage() << ptr->getEmail();
    socket->waitForBytesWritten(-1);

    std::cout<<"-- sending "<<bytes<<" Bytes"<<std::endl;

}

void ServerThread::sendMessage(DataPacket& packet){

    QDataStream out;
    out.setDevice(socket.get());
    out.setVersion(QDataStream::Qt_5_5);

    QBuffer buf;
    buf.open(QBuffer::WriteOnly);
    QDataStream tmp(&buf);

    auto strMess = std::dynamic_pointer_cast<StringMessages>(packet.getPayload());
    auto formMess = strMess->getFormattedMessages();

    //std::cout<<" --- sending "<<strMess->stringToMessages().size()<<" messages in once"<<std::endl;

    tmp << formMess;
    qint32 bytes = fixedBytesWritten + buf.data().size();

    out << bytes<<packet.getSource() << packet.getErrcode() << packet.getTypeOfData() <<
        strMess->getSiteId() << strMess->getFormattedMessages();
    socket->waitForBytesWritten(-1);

    std::cout<<"-- sending "<<bytes<<" Bytes"<<std::endl;

}

void ServerThread::sendCommand(DataPacket& packet){
    QDataStream out;
    out.setDevice(socket.get());
    out.setVersion(QDataStream::Qt_5_5);

    QBuffer buf;
    buf.open(QBuffer::WriteOnly);
    QDataStream tmp(&buf);

    auto ptr = std::dynamic_pointer_cast<Command>(packet.getPayload());
    tmp << (quint32) ptr->getCmd() << ptr->getArgs();

    qint32 bytes = fixedBytesWritten + buf.data().size();

    out << bytes<<packet.getSource() << packet.getErrcode() << packet.getTypeOfData();
    out << ptr->getSiteId() << (quint32) ptr->getCmd() << ptr->getArgs();
    socket->waitForBytesWritten(-1);

    std::cout<<"-- sending "<<bytes<<" Bytes"<<std::endl;

}

void ServerThread::sendFileInfo(DataPacket& packet){
    QDataStream out;
    out.setDevice(socket.get());
    out.setVersion(QDataStream::Qt_5_5);

    auto ptr = std::dynamic_pointer_cast<FileInfo>(packet.getPayload());

    qint32 bytes = fixedBytesWritten + sizeof(quint32);

    out << bytes<<packet.getSource() << packet.getErrcode() << (quint32)packet.getTypeOfData();
    out << ptr->getSiteId()<<(quint32) ptr->getFileInfo();
    socket->waitForBytesWritten(-1);

    std::cout<<"-- sending "<<bytes<<" Bytes"<<std::endl;

}


void ServerThread::sendCursorPos(DataPacket &packet) {
    QDataStream out;
    out.setDevice(socket.get());
    out.setVersion(QDataStream::Qt_5_5);
    QBuffer buf;
    buf.open(QBuffer::WriteOnly);
    QDataStream tmp(&buf);

    auto ptr = std::dynamic_pointer_cast<CursorPosition>(packet.getPayload());
    auto vector = QVector<quint32>();
    for (auto p : ptr->getSymbol().getPos()){
        vector.push_back(p);
    }
    // std::cout << "sendCursorPos " << ptr->getIndex() << " siteID: " << ptr->getSiteId() << std::endl;

    tmp << ptr->getSymbol().getValue() << ptr->getSymbol().getSymId().getSiteId()
        << ptr->getSymbol().getSymId().getCount() << vector << ptr->getIndex();
    qint32 bytes = fixedBytesWritten + buf.data().size();

    out << bytes << packet.getSource() << packet.getErrcode() << packet.getTypeOfData()
        << ptr->getSymbol().getValue() << ptr->getSymbol().getSymId().getSiteId()
        << ptr->getSymbol().getSymId().getCount() << vector << ptr->getIndex() << ptr->getSiteId() ;

}

void ServerThread::sendPendentDelete(QString fileName) {

    DataPacket pkt(_siteID, 0, DataPacket::command);
    auto comm = std::make_shared<Command>(_siteID,Command::rm,QVector<QString>{fileName});
    pkt.setPayload(comm);

    auto i = pendentDeleteList.find(fileName);
    if( i!=pendentDeleteList.end() )
        _sockets.broadcast(i->second,pkt);
}

void ServerThread::sendFile() {

    std::vector<Message> vm;
    int index = 0;

    // comunico al client che sto inviando il file
    {
        DataPacket pkt( 0,0,DataPacket::file_info, std::make_shared<FileInfo>(FileInfo::start,_siteID) );
        sendFileInfo(pkt);
    }

    for (auto s: _file) {
        Message m(Message::insertion, 0, s, index++);

        if ( vm.size()+1 >= 1000) {
            std::cout<<" --- sending (1) "<<vm.size()<<" messages in once"<<std::endl;
            DataPacket pkt( 0 , 0, DataPacket::textTyping, std::make_shared<StringMessages>(vm, 0) );
            sendMessage(pkt);
            std::cout<<" --- sending (2) "<<std::dynamic_pointer_cast<StringMessages>(pkt.getPayload())->stringToMessages().size()<<" messages in once"<<std::endl;
            vm.clear();
        }

        vm.push_back(m);
    }

    if( !vm.empty() ){
        DataPacket pkt( 0,0,DataPacket::textTyping,std::make_shared<StringMessages>(vm, 0));
        sendMessage(pkt);
    }

    _file.clear();

    // comunico al client che è terminato l'invio del file
    {
        DataPacket pkt(0,0,DataPacket::file_info,std::make_shared<FileInfo>(FileInfo::eof,0) );
        sendFileInfo(pkt);
    }

}

void ServerThread::disconnected(){

    if(_siteID != -1)
        _sockets.discardSocket(_siteID);

    if( operatingFileName!=""){
        _sockets.detachSocket(operatingFileName, _siteID);
        QVector<QString> vec = {operatingFileName};
        auto comm = std::make_shared<Command>(_siteID, Command::cls, vec);
        msgHandler->submit(&NetworkServer::processClsCommand,comm);

        DataPacket packet(_siteID, 0, DataPacket::cursorPos);
        auto symbol = Symbol();
        packet.setPayload(std::make_shared<CursorPosition>(symbol,-1,_siteID));
        _sockets.broadcast(operatingFileName,_siteID,packet);

    }

    socket->deleteLater();
    QSqlDatabase::removeDatabase(threadId+"_login");
    QSqlDatabase::removeDatabase(threadId+"_directories");
    QSqlDatabase::removeDatabase(threadId+"_files");
    QSqlDatabase::removeDatabase(threadId+"_filesNEW");
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
