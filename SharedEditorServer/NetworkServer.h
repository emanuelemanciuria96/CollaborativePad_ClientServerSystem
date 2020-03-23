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
#include "Packet/Symbols/Symbol.h"
#include "ServerThread.h"
#include "Packet/DataPacket.h"
#include "Packet/Message.h"

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
    std::vector<Symbol> _symbols;
    MessageHandler msgHandler;

    /* strutture condivise fra tutti i thread */
    std::mutex sym_mutex;                // struttura per il salvataggio del testo e relativo mutex
    std::mutex skt_mutex;
    std::vector<QTcpSocket*> _sockets;


protected:
    void incomingConnection(qintptr socketDesc) Q_DECL_OVERRIDE;

};


#endif //ES3_PROJ_NETWORKSERVER_NETWORKSERVER_H
