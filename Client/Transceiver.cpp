//
// Created by utente on 17/04/2020.
//

#include <iostream>
#include <QtCore/QDataStream>
#include <QtCore/QIODevice>
#include <QtCore/QBuffer>
#include "Transceiver.h"
#include "Packet/Command.h"
#include "Packet/UserInfo.h"
#include "Packet/ErrorPacket.h"

qint32 fixedBytesWritten = sizeof(qint32)+sizeof(qint32)+sizeof(quint32)+sizeof(quint32)+sizeof(qint32);
                        ///      bytes     source        errcode      DataPacket::data_t   siteID

Transceiver::Transceiver(qint32 siteID, QObject* parent):_siteID(siteID),QThread(parent) {}

void Transceiver::run() {

    openedFile = "";
    socket = new Socket();
    socket->moveToThread(this);

    timer = new QTimer();
    timer->setSingleShot(true);
    connect(timer,SIGNAL(timeout()),this,SLOT(sendAllMessages()));

    if(connectToServer() < 0)
        disconnected();


    connect(socket,&Socket::sendPacket,this,&Transceiver::sendPacket,Qt::QueuedConnection);
    connect(socket,&Socket::terminateThreadOperations,this,&Transceiver::terminateLastOperations,Qt::QueuedConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    exec(); //loop degli eventi attivato qui
}

qint32 Transceiver::connectToServer() {
    socket->connectToHost("5.95.186.15", 1234);
//    socket->connectToHost(QHostAddress::LocalHost, 1234);
    if(socket->waitForConnected(1000)) {
        connect(socket, SIGNAL(readyRead()), this, SLOT(recvPacket()), Qt::DirectConnection);
        std::cout << "Connected!" << std::endl;
        return 1;
    }
    else{
        std::cout << "Not connected: " << socket->errorString().toStdString() << std::endl;
    }

    return -1;
}

void Transceiver::recvPacket() {

    QDataStream in;
    qint32 bytes=0;
    qint32 source;
    quint32 errcode;
    quint32 type_of_data;

    //qDebug() << "Receving packet";

    in.setDevice(this->socket);
    in.setVersion(QDataStream::Qt_5_5);
    while(this->socket->bytesAvailable()>0) {
//        std::cout<<"--starting number of Available  Bytes: "<<socket->bytesAvailable()<<std::endl;
        if(this->socketSize==0) {
            in >> bytes;
            this->socketSize = bytes;
        }
        if(this->socketSize!=0 && bytes!=-14){
            if(socket->bytesAvailable() < this->socketSize-4){
                return;
            }
        }

        in >> source >> errcode >> type_of_data;
        DataPacket packet(source, errcode, (DataPacket::data_t) type_of_data);

        switch (type_of_data) {
            case (DataPacket::login): {
                recvLoginInfo(packet, in);
                break;
            }

            case (DataPacket::textTyping): {
                if(errcode == -1)
                    rollBack();
                else
                    recvMessage(packet, in);

                break;
            }
            case (DataPacket::command): {
                recvCommand(packet, in);
                break;
            }
            case (DataPacket::cursorPos):{
                recvCursorPos(packet,in);
                break;
            }
            case (DataPacket::file_info): {
                recvFileInfo(packet, in);
                break;
            }

            case (DataPacket::user_info): {
                recvUserInfo(packet, in);
                //std::cout<<"entrato nella user info"<<std::endl;
                break;
            }

            case (DataPacket::error): {
                recvErrorPacket(packet, in);
                break;
            }

            default: {
                std::cout << "Coglione c'e' un errore in tranceiver" << std::endl;
                break;
            }
        }
//        std::cout<<"--ending number of Available Bytes: "<<socket->bytesAvailable()<<std::endl;
//        std::cout<<std::endl;
        this->socketSize=0;
    }
}

void Transceiver::recvLoginInfo(DataPacket& pkt,QDataStream& in){
    qint32 siteId;
    qint32 type;
    QString user;
    QString password;
    QString name;
    QPixmap image;
    QString email;

    in >> siteId >> type >> user >> password  >> name >> image >> email;
    _siteID = siteId;
    pkt.setPayload(std::make_shared<LoginInfo>(siteId,(LoginInfo::type_t)type,user,password));
    auto ptr = std::dynamic_pointer_cast<LoginInfo>(pkt.getPayload());
    ptr->setImage(image);
    ptr->setName(name);
    ptr->setEmail(email);

    emit readyToProcess(pkt);

}

void Transceiver::recvFileInfo(DataPacket& pkt, QDataStream& in){
    qint32 siteId;
    qint32 type;
    QString serverFileName;

    in>>siteId>>type>>serverFileName;
    pkt.setPayload(std::make_shared<FileInfo>(siteId,(FileInfo::file_info_t)type,serverFileName));

    if( type == FileInfo::start)
        openedServerFile = serverFileName;

    emit readyToProcess(pkt);

}

void Transceiver::recvMessage(DataPacket& pkt, QDataStream& in) {

    qint32 siteId;
    QVector<Message> msgs;
    QString file;

    in.setDevice(socket);
    in.setVersion(QDataStream::Qt_5_5);

    in >> siteId;
    auto ptr = std::make_shared<StringMessages>(siteId);
    qint32 numBytes;

    in >> numBytes;
    auto stringBytes = socket->bytesAvailable();
    in>>file;
    stringBytes -= socket->bytesAvailable();

    numBytes-=stringBytes;
    while( numBytes > 0 ){
        auto tmp = socket->bytesAvailable();
        qint32 action;
        qint32 messSiteId;
        qint32 localIndx;
        QChar value;
        short alignment;
        qint32 symSiteId;
        quint32 counter;
        QVector<quint32> pos;
        QTextCharFormat format;

        in >> action >> messSiteId >> localIndx >> value >> alignment >> symSiteId >> counter >> pos >> format;

        auto stdVecPos = pos.toStdVector();
        Symbol s(value,symSiteId,counter,stdVecPos);
        s.setFormat(format);
        s.setAlignmentType(alignment);
        Message m((Message::action_t)action,messSiteId,s,localIndx);

        ptr->appendMessage(m);
        numBytes-=(tmp-socket->bytesAvailable());
    }

    ptr->setFileName(file);
    pkt.setPayload(ptr);

    auto num = std::dynamic_pointer_cast<StringMessages>(pkt.getPayload())->size();
    std::cout<<" --- number of arrived messages at once "<<num <<std::endl;

    if( file != openedServerFile)
        return;

    emit readyToProcess(pkt);

}

void Transceiver::recvCommand(DataPacket& pkt, QDataStream &in) {
    qint32 siteId;
    quint32 cmd;
    QVector<QString> args;

    in >> siteId >> cmd >> args;

    switch( cmd ){
        case Command::ren:
            if(openedFile==args.first())
                openedFile = args.last();
            break;
        case Command::rm:
            if( openedFile == args.first())
                messages.clear();
            openedFile = "";
            openedServerFile = "";
            break;
    }

    pkt.setPayload( std::make_shared<Command>(siteId,(Command::cmd_t)cmd,std::move(args)));

    emit readyToProcess(pkt);
}

void Transceiver::recvCursorPos(DataPacket &pkt, QDataStream &in) {
    qint32 siteId;
    qint32 index;
    QChar ch;
    qint32 symbol_siteId;
    qint32 count;
    QVector<quint32> pos;
    QString fileName;

    in >> ch >> symbol_siteId >> count >> pos >> index >> siteId >> fileName;
    std::cout << "Dentro recv " << siteId << " pos:" << index << std::endl;
    auto pos_std = pos.toStdVector();
    auto symbol = Symbol(ch,symbol_siteId,count,pos_std);

    if( fileName != openedServerFile )
        return;

    pkt.setPayload(std::make_shared<CursorPosition>(symbol,index,siteId));

    emit readyToProcess(pkt);

}

void Transceiver::recvUserInfo(DataPacket &pkt, QDataStream &in) {
    qint32 siteId;
    qint32 type;
    QString username;
    QPixmap image;
    QString name;
    QString email;
    QString fileName;

    in >> siteId >> type >> fileName >> username >> image >> name >> email;

    if(fileName != openedServerFile )
        return;

    pkt.setPayload(std::make_shared<UserInfo>(siteId,(UserInfo::info_t)type,username,image, name, email));

    emit readyToProcess(pkt);

}

void Transceiver::recvErrorPacket(DataPacket &pkt, QDataStream &in) {
    qint32 siteId;
    QString message;

    in >> siteId >> message;

    pkt.setPayload(std::make_shared<ErrorPacket>(siteId, message));

    emit readyToProcess(pkt);
}

void Transceiver::sendPacket(DataPacket pkt){

    switch(pkt.getTypeOfData()){
        case (DataPacket::login): {
            sendLoginInfo(pkt);
            break;
        }

        case (DataPacket::textTyping): {
            sendMessage(pkt);
            break;
        }

        case (DataPacket::command): {
            sendCommand(pkt);
            break;
        }

        case (DataPacket::cursorPos):{
            sendCursorPos(pkt);
            break;
        }

        case (DataPacket::user_info):{
            sendUserInfo(pkt);
            break;
        }

        default: {
            std::cout<<"Coglione c'è un errore"<<std::endl;
        }
    }

}

void Transceiver::sendAllMessages() {

    if( messages.empty() ) return;

    firstMessage = true;

    QDataStream out;
    out.setDevice(socket);
    out.setVersion(QDataStream::Qt_5_5);

    QBuffer buf;
    buf.open(QBuffer::ReadWrite);
    QDataStream tmp(&buf);

    int num_mess = messages.size();
    auto strMess = std::make_shared<StringMessages>(messages,_siteID,openedServerFile);
    num_mess-=messages.size();

    auto file = strMess->getFileName();
    tmp<<file;

    for(auto m : strMess->getQueue()){
        auto sym = m.getSymbol();
        tmp<<m.getAction()<<m.getSiteId()<<m.getLocalIndex()
           <<sym.getValue()<<sym.getAlignmentType()<<sym.getSymId().getSiteId()<<sym.getSymId().getCount()
           <<QVector<quint32>::fromStdVector(sym.getPos())<<sym.getFormat();
    }

    qint32 bytes = fixedBytesWritten + buf.data().size() + 4; //+4 perche' buf.data() aggiunge numero di bytes

    DataPacket pkt(_siteID, 0,DataPacket::textTyping,strMess);
    out << bytes << _siteID << pkt.getErrcode() << (quint32)DataPacket::textTyping
        << strMess->getSiteId() << buf.data();

    socket->waitForBytesWritten(-1);

//    std::cout<<" --- sending "<<num_mess<<" messages in once"<<std::endl;

    if( !messages.empty() ) {
        timer->start(100);
        firstMessage = false;
    }

}

void Transceiver::sendMessage(DataPacket& packet) {

   if(firstMessage){
        timer->start(200);
        firstMessage = false;
   }

   messages.push_back(*std::static_pointer_cast<Message>(packet.getPayload()));

}

void Transceiver::sendLoginInfo(DataPacket& packet){

    QDataStream out;
    auto ptr = std::dynamic_pointer_cast<LoginInfo>(packet.getPayload());
    out.setDevice(socket);
    out.setVersion(QDataStream::Qt_5_5);

    QBuffer buf;
    buf.open(QBuffer::WriteOnly);
    QDataStream tmp(&buf);
    tmp<<(quint32) ptr->getType() << ptr->getUser() << ptr->getPassword() << ptr->getName() << ptr->getImage() << ptr->getEmail();

    qint32 bytes = fixedBytesWritten + buf.data().size();

    out << bytes << packet.getSource() << packet.getErrcode() << (quint32) packet.getTypeOfData();
    out << ptr->getSiteId() << (quint32) ptr->getType() << ptr->getUser() << ptr->getPassword() << ptr->getName() << ptr->getImage() << ptr->getEmail();
    socket->waitForBytesWritten(-1);

}

void Transceiver::sendCommand(DataPacket& packet){

    QDataStream out;
    auto ptr = std::dynamic_pointer_cast<Command>(packet.getPayload());
    out.setDevice(socket);
    out.setVersion(QDataStream::Qt_5_5);

    QBuffer buf;
    buf.open(QBuffer::WriteOnly);
    QDataStream tmp(&buf);
    tmp << (quint32) ptr->getCmd() << ptr->getArgs();
    qint32 bytes = fixedBytesWritten + buf.data().size();

    switch( ptr->getCmd() ) {
        case Command::cls:
            while (!messages.empty())
                sendAllMessages();
            openedFile = "";
            openedServerFile = "";
            break;
        case Command::opn:
            openedFile = ptr->getArgs().first();
            break;
        case Command::rm:
            if(openedFile==ptr->getArgs().first()) {
                messages.clear();
                openedFile = "";
                openedServerFile = "";
            }
            break;
        case Command::ren:
            if(openedFile==ptr->getArgs().first()) {
                openedFile = ptr->getArgs().last();
            }
            break;
        default:
            break;
    }

    out <<bytes<< packet.getSource() << packet.getErrcode() << (quint32)packet.getTypeOfData();
    out << ptr->getSiteId() << (quint32) ptr->getCmd() << ptr->getArgs();
    socket->waitForBytesWritten(-1);

}

void Transceiver::sendCursorPos(DataPacket &pkt) {
    QDataStream out;
    out.setDevice(socket);
    out.setVersion(QDataStream::Qt_5_5);
    QBuffer buf;
    buf.open(QBuffer::WriteOnly);
    QDataStream tmp(&buf);

    auto ptr = std::dynamic_pointer_cast<CursorPosition>(pkt.getPayload());
    ptr->setFileName(openedServerFile);
    auto vector = QVector<quint32>::fromStdVector(ptr->getSymbol().getPos());

    tmp << ptr->getSymbol().getValue() << ptr->getSymbol().getSymId().getSiteId()
        << ptr->getSymbol().getSymId().getCount() << vector << ptr->getIndex() << ptr->getFileName();
    qint32 bytes = fixedBytesWritten + buf.data().size();

    out << bytes << pkt.getSource() << pkt.getErrcode() << pkt.getTypeOfData()
        << ptr->getSymbol().getValue() << ptr->getSymbol().getSymId().getSiteId()
        << ptr->getSymbol().getSymId().getCount() << vector << ptr->getIndex() << ptr->getSiteId() << ptr->getFileName();

    //std::cout << "sending cursor index " << ptr->getSiteId() << " " << ptr->getIndex() << std::endl;

    socket->waitForBytesWritten(-1);
}

void Transceiver::sendUserInfo(DataPacket &pkt) {

    QDataStream out;
    out.setDevice(socket);
    out.setVersion(QDataStream::Qt_5_5);
    QBuffer buf;
    buf.open(QBuffer::WriteOnly);
    QDataStream tmp(&buf);

    auto ptr = std::dynamic_pointer_cast<UserInfo>(pkt.getPayload());

    tmp << (quint32) ptr->getType() << openedServerFile << ptr->getUsername() << ptr->getImage() << ptr->getName() << ptr->getEmail();

    qint32 bytes = fixedBytesWritten + buf.data().size();

    out << bytes << pkt.getSource() << pkt.getErrcode() << (quint32)pkt.getTypeOfData();
    out << ptr->getSiteId() << (quint32) ptr->getType() << openedServerFile << ptr->getUsername() << ptr->getImage() << ptr->getName() << ptr->getEmail();
    socket->waitForBytesWritten(-1);
}

void Transceiver::disconnected(){
    if (logout)
        return;
    socket->deleteLater();
    timer->deleteLater();
    std::cout<<"Server unavailable!"<<std::endl;
    exit(1);
}

void Transceiver::rollBack(){
    emit deleteText();
}

void Transceiver::terminateLastOperations() {
    while (!messages.empty())
        sendAllMessages();
    timer->deleteLater();
    logout = true;
    socket->deleteLater();
    exit(0);
}
