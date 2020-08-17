//
// Created by utente on 17/04/2020.
//

#include <iostream>
#include <QtCore/QDataStream>
#include <QtCore/QIODevice>
#include <QtCore/QBuffer>
#include "Transceiver.h"
#include "Packet/Command.h"

qint32 fixedBytesWritten = sizeof(qint32)+sizeof(qint32)+sizeof(quint32)+sizeof(quint32)+sizeof(qint32);
                        ///      bytes     source        errcode      DataPacket::data_t   siteID

Transceiver::Transceiver(qint32 siteID, QObject* parent):_siteID(siteID),QThread(parent) {}

void Transceiver::run() {

    socket = new Socket();
    socket->moveToThread(this);

    connectToServer();

    connect(socket,&Socket::sendPacket,this,&Transceiver::sendPacket,Qt::QueuedConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    timer = new QTimer();
    timer->setSingleShot(true);
    connect(timer,SIGNAL(timeout()),this,SLOT(sendAllMessages()));

    exec(); //loop degli eventi attivato qui
}

qint32 Transceiver::connectToServer() {
    socket->connectToHost(QHostAddress::LocalHost, 1234);
    //socket->connectToHost(QHostAddress::LocalHost, 1234);
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
        std::cout<<"--starting number of Available  Bytes: "<<socket->bytesAvailable()<<std::endl;
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
            case (DataPacket::file_info): {
                recvFileInfo(packet, in);
                break;
            }

            default: {
                std::cout << "Coglione c'e' un errore" << std::endl;
                break;
            }
        }
        std::cout<<"--ending number of Available Bytes: "<<socket->bytesAvailable()<<std::endl;
        std::cout<<std::endl;
        this->socketSize=0;
    }
}

void Transceiver::recvLoginInfo(DataPacket& pkt,QDataStream& in){
    qint32 siteId;
    qint32 type;
    QString user;
    QString password;

    in >> siteId >> type >> user >> password;
    _siteID = siteId;
    pkt.setPayload(std::make_shared<LoginInfo>(siteId,(LoginInfo::type_t)type,user,password));

    emit readyToProcess(pkt);

}

void Transceiver::recvFileInfo(DataPacket& pkt, QDataStream& in){
    qint32 siteId;
    qint32 type;

    in>>siteId>>type;
    pkt.setPayload(std::make_shared<FileInfo>(siteId,(FileInfo::file_info_t)type));

    emit readyToProcess(pkt);

}

void Transceiver::recvMessage(DataPacket& pkt, QDataStream& in) {

    qint32 siteId;
    QString formattedMessages;

    in.setDevice(socket);
    in.setVersion(QDataStream::Qt_5_5);

    in >> siteId >> formattedMessages;

    pkt.setPayload(std::make_shared<StringMessages>(formattedMessages,siteId));
    emit readyToProcess(pkt);

    std::cout<<"receaving some messages"<<std::endl;

}

void Transceiver::recvCommand(DataPacket& pkt, QDataStream &in) {
    qint32 siteId;
    quint32 cmd;
    QVector<QString> args;

    in >> siteId >> cmd >> args;

    pkt.setPayload( std::make_shared<Command>(siteId,(Command::cmd_t)cmd,std::move(args)));

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

        default: {
            std::cout<<"Coglione c'è un errore"<<std::endl;
        }
    }

}

void Transceiver::sendAllMessages() {

    firstMessage = true;

    QDataStream out;
    out.setDevice(socket);
    out.setVersion(QDataStream::Qt_5_5);

    QBuffer buf;
    buf.open(QBuffer::WriteOnly);
    QDataStream tmp(&buf);

    auto *strMess = new StringMessages(messages,_siteID);
    auto formMess = strMess->getFormattedMessages();
    tmp << formMess;
    qint32 bytes = fixedBytesWritten + buf.data().size();
    DataPacket pkt(_siteID,0,DataPacket::textTyping,strMess);
    out << bytes << _siteID << 0 <<(quint32) DataPacket::textTyping <<
         strMess->getSiteId() << formMess;

    socket->waitForBytesWritten(-1);

    std::cout<<"-- sending "<<bytes<<" Bytes"<<std::endl;

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

   messages.push_back(*std::dynamic_pointer_cast<Message>(packet.getPayload()));

}

void Transceiver::sendLoginInfo(DataPacket& packet){

    QDataStream out;
    auto ptr = std::dynamic_pointer_cast<LoginInfo>(packet.getPayload());
    out.setDevice(socket);
    out.setVersion(QDataStream::Qt_5_5);

    QBuffer buf;
    buf.open(QBuffer::WriteOnly);
    QDataStream tmp(&buf);
    tmp<<(quint32) ptr->getType() << ptr->getUser() << ptr->getPassword();

    qint32 bytes = fixedBytesWritten + buf.data().size();

    out << bytes << packet.getSource() << packet.getErrcode() << (quint32) packet.getTypeOfData();
    out << ptr->getSiteId() << (quint32) ptr->getType() << ptr->getUser() << ptr->getPassword();
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

    out <<bytes<< packet.getSource() << packet.getErrcode() << (quint32)packet.getTypeOfData();
    out << ptr->getSiteId() << (quint32) ptr->getCmd() << ptr->getArgs();
    socket->waitForBytesWritten(-1);

}

void Transceiver::disconnected(){

    socket->deleteLater();
    timer->deleteLater();
    std::cout<<"Server unavailable!"<<std::endl;
    exit(0);
}

void Transceiver::rollBack(){
    emit deleteText();
}
