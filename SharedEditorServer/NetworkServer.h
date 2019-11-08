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
#include "Message.h"
#include "Symbol.h"
#include "ServerThread.h"

class NetworkServer : public QTcpServer
{
Q_OBJECT
public:
    explicit NetworkServer(QObject *parent = 0);
    NetworkServer(const NetworkServer& ns) = delete;
    void startServer();
    void sendMessage(Message& m);
    //void localInsert(qint32 index, QChar value);
    //void localErase( qint32 index );
    void process( const Message& m);
    void to_string();

public slots:
    void recvMessage();
    void deleteSocket();
    void testServer(){}

    signals:
    void startTest();

private:
    qint32 _counter;
    QTcpSocket *socket;

    /* strutture condivise fra tutti i thread */
    std::mutex sym_mutex;                // struttura per il salvataggio del testo e relativo mutex
    std::vector<Symbol> _symbols;
    std::mutex skt_mutex;
    std::vector<QTcpSocket*> _sockets;


protected:
    void incomingConnection(qintptr socketDesc) Q_DECL_OVERRIDE;

};


#endif //ES3_PROJ_NETWORKSERVER_NETWORKSERVER_H
