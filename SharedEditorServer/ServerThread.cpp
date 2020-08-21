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
qint32 fixedBytesWritten = sizeof(qint32)+sizeof(qint32)+sizeof(quint32)+sizeof(quint32)+sizeof(qint32);
///      bytes     source        errcode      DataPacket::data_t   siteID



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
    QSqlDatabase::addDatabase("QSQLITE", threadId+"_filesNEW");

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
        //std::cout<<"--ending number of Available Bytes: "<<socket->bytesAvailable()<<std::endl;
        std::cout<<std::endl;
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

    in >> siteId >> type >> user >> password >> name >> image;

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
/*****************************
            /// in mancanza di un client che mi chieda di ricevere un file, faccio questo nella
            /// procedura di login
                QString name = QString::fromStdString("/prova1>F");
                std::cout << name.toStdString() << std::endl;
                QVector<QString> vec = {name};
                auto comm = std::make_shared<Command>(_siteID, Command::opn, vec);

                QString fileName = comm->opnCommand(threadId);
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
*****************************/
        } else {
            std::cout << "client not logged!" << std::endl;
            sendPacket(packet);
        }
    } else if (type == LoginInfo::update_info && !_username.isEmpty()) {
        auto shr = std::make_shared<LoginInfo>( _siteID, (LoginInfo::type_t)type, "", "");
        shr->setImage(image);
        shr->setName(name);
        shr->updateInfo(threadId);
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
            command->cdCommand(threadId);
            sendPacket(packet);
            break;
        }

        case (Command::mkdir):{
            if(command->mkdirCommand(threadId))
                std::cout << "mkdir command ok!" << std::endl;
            else
                std::cout << "mkdir command failed!" << std::endl;
            break;
        }

        case (Command::rm):{
            if(command->rmCommand(threadId))
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
            std::cout << "file requested: "<<command->getArgs().front().toStdString() << std::endl;
            if( command->opnCommand(threadId) ) {

                QString fileName = command->getArgs().front();

                if( operatingFileName != "" ) {
                    _sockets.detachSocket(operatingFileName, _siteID);
                    QVector<QString> vec = {operatingFileName};
                    auto comm = std::make_shared<Command>(_siteID, Command::cls, vec);
                    msgHandler->submit(&NetworkServer::processClsCommand,comm);
                }

                operatingFileName = fileName;
                _sockets.attachSocket(fileName,_siteID,socket.get());
                std::cout << fileName.toStdString() << std::endl;
                msgHandler->submit(&NetworkServer::processOpnCommand, command);

            }else
                std::cout << "opn command failed!" << std::endl;

            break;
        }

        case (Command::tree):{
            command->treeCommand(threadId);
            sendPacket(packet);
            break;
        }

        case (Command::cls):{
            if( operatingFileName!="" && command->opnCommand(threadId)) {
                _sockets.detachSocket(operatingFileName, _siteID);
                msgHandler->submit(&NetworkServer::processClsCommand, command);
            }else
                std::cout << "cls command failed!" << std::endl;

            break;
        }

        case (Command::ls):{
            command->lsCommand(threadId);
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

    std::cout << "Dentro recv " << siteId << " pos:" << index << std::endl;

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
    tmp<<(quint32) ptr->getType() << ptr->getUser() << ptr->getPassword() << ptr->getName() << ptr->getImage();

    qint32 bytes = fixedBytesWritten + buf.data().size();

    out << bytes<<packet.getSource() << packet.getErrcode() << (quint32) packet.getTypeOfData();
    out << ptr->getSiteId() << (quint32) ptr->getType() << ptr->getUser() << ptr->getPassword() << ptr->getName() << ptr->getImage();
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
    std::cout << "sendCursorPos " << ptr->getIndex() << " siteID: " << ptr->getSiteId() << std::endl;

    tmp << ptr->getSymbol().getValue() << ptr->getSymbol().getSymId().getSiteId()
        << ptr->getSymbol().getSymId().getCount() << vector << ptr->getIndex();
    qint32 bytes = fixedBytesWritten + buf.data().size();

    out << bytes << packet.getSource() << packet.getErrcode() << packet.getTypeOfData() <<
        ptr->getSymbol().getValue() << ptr->getSymbol().getSymId().getSiteId()
        << ptr->getSymbol().getSymId().getCount() << vector << ptr->getIndex() << ptr->getSiteId() ;

}

void ServerThread::disconnected()
{
    DataPacket packet(_siteID, 0, DataPacket::cursorPos);
    auto symbol = Symbol();
    packet.setPayload(std::make_shared<CursorPosition>(symbol,-1,_siteID));
    _sockets.broadcast(operatingFileName,_siteID,packet);

    if( operatingFileName!=""){
        _sockets.detachSocket(operatingFileName, _siteID);
        QVector<QString> vec = {operatingFileName};
        auto comm = std::make_shared<Command>(_siteID, Command::opn, vec);
        msgHandler->submit(&NetworkServer::processClsCommand,comm);
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
