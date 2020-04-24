//
// Created by utente on 17/04/2020.
//

#ifndef CLIENT_TRANSCEIVER_H
#define CLIENT_TRANSCEIVER_H

#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include "Socket.h"
#include "Packet/DataPacket.h"
#include "Packet/Message.h"
#include "Packet/LoginInfo.h"
#include "Packet/Payload.h"

class Transceiver: public QThread {

    Q_OBJECT
public:
    void run() override;
    Transceiver(QObject* parent = nullptr);
    Socket* getSocket(){ return socket; };

public slots:
    void recvPacket();
    void sendPacket(DataPacket pkt);
    void disconnected();

signals:
    void readyToProcess(DataPacket pkt);

private:
    Socket *socket;
    qintptr socketDescriptor;

    qint32 connectToServer();

    void sendLoginInfo(DataPacket& pkt);
    void sendMessage(DataPacket& pkt);
    void recvLoginInfo(DataPacket& pkt, QDataStream& in);
    void recvMessage(DataPacket& pkt,QDataStream& in);
};


#endif //CLIENT_TRANSCEIVER_H
