//
// Created by utente on 17/04/2020.
//

#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <QTcpSocket>
#include <mutex>
#include "Packet/DataPacket.h"
#include <QObject>

class Socket: public QTcpSocket {
Q_OBJECT

public:
    explicit Socket(QObject *parent = 0):QTcpSocket(parent){}

signals:
    void sendPacket(DataPacket pkt);

};

#endif //CLIENT_SOCKET_H
