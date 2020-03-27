//
// Created by utente on 03/11/2019.
//

#ifndef ES3_PROJ_NETWORKSERVER_SERVERTHREAD_H
#define ES3_PROJ_NETWORKSERVER_SERVERTHREAD_H

#include "Packet/DataPacket.h"
#include <QThread>
#include <QTcpSocket>
#include <QtCore/QMutex>
#include <shared_mutex>
#include "NetworkServer.h"
#include "Packet/Symbols/Symbol.h"
#include "Packet/Message.h"
#include "Packet/LoginInfo.h"
#include "MessageHandler.h"

class ServerThread : public QThread{
Q_OBJECT

public:
    explicit ServerThread(qintptr socketDescriptor, MessageHandler *msgHandler,QObject *parent =0);
    void run() override;

signals:
    void error(QTcpSocket::SocketError socketerror);    //slot che gestisce questo segnale da implementare

public slots:
    void recvPacket();
    void recvMessage(DataPacket& packet);
    void disconnected();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;

    MessageHandler *msgHandler;
    static std::shared_mutex skt_mutex;
    static std::vector<std::pair<QTcpSocket*,std::mutex*>> _sockets;

    void sendMessage(DataPacket& packet, QTcpSocket *skt, std::mutex *mtx);
    void sendPacket(DataPacket& packet, QTcpSocket *skt, std::mutex *mtx = nullptr);
    bool isLogged;
    qint32 login(DataPacket& packet);
    LoginInfo loadLoginJson(std::string dir);
    void saveFileJson(std::string dir,std::vector<Symbol> _symbols);
    std::vector<Symbol> loadFileJson(std::string dir);
};


#endif //ES3_PROJ_NETWORKSERVER_SERVERTHREAD_H
