//
// Created by utente on 17/04/2020.
//

#ifndef CLIENT_TRANSCEIVER_H
#define CLIENT_TRANSCEIVER_H

#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtCore/QTimer>
#include <deque>
#include "Socket.h"
#include "Packet/DataPacket.h"
#include "Packet/Message.h"
#include "Packet/LoginInfo.h"
#include "Packet/Payload.h"
#include "Packet/StringMessages.h"
#include "Packet/FileInfo.h"

class Transceiver: public QThread {

    Q_OBJECT
public:
    void run() override;
    Transceiver(qint32 siteID,QObject* parent = 0);
    Socket* getSocket(){ return socket; };
    void setSiteId( qint32 siteID ){ _siteID = siteID; }

public slots:
    void recvPacket();
    void sendPacket(DataPacket pkt);
    void sendAllMessages();
    void disconnected();

signals:
    void readyToProcess(DataPacket pkt);
    void deleteText();

private:
    qint32 _siteID;
    std::vector<Message> messages;
    bool firstMessage = true;
    Socket *socket;
    qintptr socketDescriptor;
    QTimer *timer;
    qint32 socketSize=0;

    qint32 connectToServer();

    void sendLoginInfo(DataPacket& pkt);
    void sendMessage(DataPacket& pkt);
    void sendCommand(DataPacket& pkt);

    void recvLoginInfo(DataPacket& pkt, QDataStream& in);
    void recvFileInfo(DataPacket& pkt, QDataStream& in);
    void recvMessage(DataPacket& pkt,QDataStream& in);

    void rollBack();

    void recvCommand(DataPacket& pkt,QDataStream& in);


};


#endif //CLIENT_TRANSCEIVER_H

