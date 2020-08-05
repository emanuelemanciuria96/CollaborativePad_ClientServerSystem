//
// Created by utente on 03/11/2019.
//

#ifndef ES3_PROJ_NETWORKSERVER_SERVERTHREAD_H
#define ES3_PROJ_NETWORKSERVER_SERVERTHREAD_H

#include "Packet/DataPacket.h"
#include "Packet/StringMessages.h"
#include <QThread>
#include <QTcpSocket>
#include <QtCore/QMutex>
#include <shared_mutex>
#include "Packet/Symbols/Symbol.h"
#include "Packet/Message.h"
#include "Packet/LoginInfo.h"
#include "Packet/Command.h"
#include "MessageHandler.h"
#include "Socket.h"
#include "SocketsPool.h"


class ServerThread : public QThread{
Q_OBJECT

public:
    explicit ServerThread(qintptr socketDesc, MessageHandler *msgHandler,QObject *parent = 0);
    void run() override;
    QString getOperatingFileName(){ return operatingFileName; }
    quint32 getSiteID(){ return _siteID; }
    QString& getUsername(){ return _username; }
    std::shared_ptr<Socket> getSocket(){ return socket; }
    void registerToSocketsList();

signals:
    void error(QTcpSocket::SocketError socketerror);    //slot che gestisce questo segnale da implementare
    void deleteMe(QPointer<QThread> th);
    void recordThread(QPointer<QThread> th);

public slots:
    void recvPacket();
    void sendPacket(DataPacket packet);
    void disconnected();

private:
    std::shared_ptr<Socket> socket;
    qintptr socketDescriptor;
    std::shared_ptr<MessageHandler> msgHandler;
    static SocketsPool _sockets; // l'oggetto è thread safe
    QString _username;
    qint32 _siteID;
    QString threadId;
    QString operatingFileName;


    void recvLoginInfo(DataPacket& packet, QDataStream& in);
    void recvMessage(DataPacket& packet,QDataStream& in);
    void recvCommand(DataPacket& packet,QDataStream& in);

    void sendLoginInfo(DataPacket& packet);
    void sendMessage(DataPacket& packet);
    void sendCommand(DataPacket& packet);

    void setThreadId();

};


#endif //ES3_PROJ_NETWORKSERVER_SERVERTHREAD_H
