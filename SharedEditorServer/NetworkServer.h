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

class NetworkServer: public QTcpServer{
Q_OBJECT
public:
    explicit NetworkServer(QObject *parent = 0);
    NetworkServer(const NetworkServer& ns) = delete;
    void startServer();
    void to_string();

    static void localInsert(Message m);
    static void localErase(Message m);

private:
    qint32 _counter;
    QTcpSocket *socket;
    std::shared_ptr<MessageHandler> msgHandler;
    static std::vector<Symbol> _symbles;    // struttura per il salvataggio del testo
    // static std::mutex sym_mutex;  per ora questo mutex non serve: ci accede un solo thread, che è quello creato in MessageHandler
    /* strutture condivise fra tutti i thread */
    std::shared_mutex skt_mutex;
    std::vector<QTcpSocket*> _sockets;


protected:
    void incomingConnection(qintptr socketDesc) Q_DECL_OVERRIDE;

};


#endif //ES3_PROJ_NETWORKSERVER_NETWORKSERVER_H
