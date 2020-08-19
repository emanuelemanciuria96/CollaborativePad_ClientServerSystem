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
#include "Packet/CursorPosition.h"
#include "Packet/Symbols/Symbol.h"

class Transceiver: public QThread {

    Q_OBJECT
public:
    void run() override;
    Transceiver(quint32 siteID,QObject* parent = nullptr);
    Socket* getSocket(){ return socket; };

public slots:
    void recvPacket();
    void sendPacket(DataPacket pkt);
    void sendAllMessages();
    void disconnected();

signals:
    void readyToProcess(DataPacket pkt);
    void deleteText();

private:
    quint32 _siteID;
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
    void sendCursorPos(DataPacket& packet);

    void recvLoginInfo(DataPacket& pkt, QDataStream& in);
    void recvMessage(DataPacket& pkt,QDataStream& in);

    void rollBack();

    void recvCommand(DataPacket& pkt,QDataStream& in);
    void recvCursorPos(DataPacket& packet, QDataStream& in);

};


#endif //CLIENT_TRANSCEIVER_H

