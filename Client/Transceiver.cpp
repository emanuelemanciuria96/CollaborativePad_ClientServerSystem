//
// Created by utente on 17/04/2020.
//

#include <iostream>
#include <QtCore/QDataStream>
#include "Transceiver.h"

Transceiver::Transceiver(QObject* parent):QThread(parent) {}

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
    qint32 source;
    quint32 errcode;
    quint32 type_of_data;

    //qDebug() << "Receving packet";

    in.setDevice(this->socket);
    in.setVersion(QDataStream::Qt_5_5);

    in >> source >> errcode >> type_of_data;
    DataPacket packet(source, errcode, (DataPacket::data_t)type_of_data);

    switch (type_of_data) {
        case (DataPacket::login): {
            recvLoginInfo(packet,in);
            break;
        }

        case (DataPacket::textTyping): {
            recvMessage(packet,in);
            break;
        }

        default: {
            std::cout << "Coglione c'e' un errore" << std::endl;
            break;
        }
    }

    //if(this->socket->bytesAvailable()>0)         //se arrivano dati troppo velocemente la recvMessage() non fa in tempo
    //        emit socket->readyRead();                //a processare i segnali readyRead() e i dati rimangono accodati
}                                                //sul socket, in questo modo svuoto la coda richiamando la recvMessage()

void Transceiver::recvLoginInfo(DataPacket& pkt,QDataStream& in){
    qint32 siteId;
    qint32 type;
    QString user;
    QString password;

    in >> siteId >> type >> user >> password;

    pkt.setPayload(std::make_shared<LoginInfo>(siteId,(LoginInfo::type_t)type,user,password));

    emit readyToProcess(pkt);

}

void Transceiver::recvMessage(DataPacket& pkt, QDataStream& in) {

    qint32 siteId;
    QString formattedMessages;

    in.setDevice(this->socket);
    in.setVersion(QDataStream::Qt_5_5);

    in >> siteId >> formattedMessages;

    pkt.setPayload(std::make_shared<StringMessages>(formattedMessages,siteId));

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

    qint32 siteID = messages[0].getSiteId();
    auto *strMess = new StringMessages(messages,siteID);
    DataPacket pkt(siteID,0,DataPacket::textTyping,strMess);
    out << pkt.getSource() << pkt.getErrcode() << pkt.getTypeOfData() <<
         strMess->getSiteId() << strMess->getFormattedMessages() ;
    socket->waitForBytesWritten(-1);
    if( !messages.empty() ) {
        timer->start(100);
        firstMessage = false;
    }

/*
    qint32 num=ptr->getSymbol().getPos().size();
    out << packet.getSource() << packet.getErrcode() << packet.getTypeOfData();
    out << ptr->getSiteId() << (qint32)ptr->getAction() << ptr->getSymbol().getValue() << ptr->getSymbol().getSymId().getSiteId() << ptr->getSymbol().getSymId().getCount() << num;
    for(auto i : ptr->getSymbol().getPos())
        out << (qint32) i;
*/


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

    out << packet.getSource() << packet.getErrcode() << packet.getTypeOfData();
    out << ptr->getSiteId() << ptr->getType() << ptr->getUser() << ptr->getPassword();
    socket->waitForBytesWritten(-1);

}

void Transceiver::disconnected(){

    socket->deleteLater();
    timer->deleteLater();
    std::cout<<"Server unavailable!"<<std::endl;
    exit(0);
}
