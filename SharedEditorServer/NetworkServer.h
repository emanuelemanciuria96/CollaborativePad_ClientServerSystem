//
// Created by muska on 15/10/2019.
//

#ifndef ES3_PROJ_NETWORKSERVER_NETWORKSERVER_H
#define ES3_PROJ_NETWORKSERVER_NETWORKSERVER_H


#include <iostream>
#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <thread>
#include <shared_mutex>
#include "Packet/Symbols/Symbol.h"
#include "ServerThread.h"
#include "Packet/DataPacket.h"
#include "Packet/Message.h"
#include "MessageHandler.h"
#include "Socket.h"
#include <QtCore/QPointer>

class NetworkServer: public QTcpServer{
Q_OBJECT
public:
    explicit NetworkServer(QObject *parent = 0);
    NetworkServer(const NetworkServer& ns) = delete;
    ~NetworkServer();
    void startServer();
    static void to_string();

    static void localInsert(Payload &pl);
    static void localErase(Payload &pl);

public slots:
    void deleteThread(QPointer<QThread> th);
    void recordThread(QPointer<QThread> th);

private:
    std::shared_ptr<MessageHandler> msgHandler;
    static std::vector<Symbol> _symbles;    // struttura per il salvataggio del testo
    std::map<quint32,std::shared_ptr<Socket>> active_sockets;
    QString threadId;

    void setThreadId();
    // static std::mutex sym_mutex;  per ora questo mutex non serve: ci accede un solo thread, che è quello creato in MessageHandler

protected:
    void incomingConnection(qintptr socketDesc) Q_DECL_OVERRIDE;

};


#endif //ES3_PROJ_NETWORKSERVER_NETWORKSERVER_H
