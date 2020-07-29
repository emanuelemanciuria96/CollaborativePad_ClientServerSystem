//
// Created by utente on 03/04/2020.
//

#ifndef SHAREDEDITORSERVER_SOCKET_H
#define SHAREDEDITORSERVER_SOCKET_H

#include <QTcpSocket>
#include <mutex>
#include "Packet/DataPacket.h"
#include <QObject>

class Socket: public QTcpSocket {
Q_OBJECT

public:
    explicit Socket(QObject *parent = 0):QTcpSocket(parent){}

signals:
    void sendMessage(DataPacket pkt,std::mutex *mtx = nullptr);

};


#endif //SHAREDEDITORSERVER_SOCKET_H
