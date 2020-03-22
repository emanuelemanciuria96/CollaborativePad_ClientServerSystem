//
// Created by utente on 03/11/2019.
//

#ifndef ES3_PROJ_NETWORKSERVER_SERVERTHREAD_H
#define ES3_PROJ_NETWORKSERVER_SERVERTHREAD_H


#include <QThread>
#include <QTcpSocket>
#include <QtCore/QMutex>
#include "NetworkServer.h"
#include "Packet/Symbols/Symbol.h"
#include "Packet/Message.h"


class ServerThread : public QThread{
Q_OBJECT

public:
    explicit ServerThread(qintptr socketDescriptor, std::mutex *sym_mutex, std::vector<Symbol> *symbols,
                          std::mutex *skt_mutex,std::vector<QTcpSocket*> *sockets ,QObject *parent =0);
    void run() override;

signals:
    void error(QTcpSocket::SocketError socketerror);    //slot che gestisce questo segnale da implementare

public slots:
    void recvMessage();
    void disconnected();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;

    std::mutex *skt_mutex;
    std::vector<QTcpSocket*> *_sockets;
    std::vector<Symbol> *_symbols;
    std::mutex *sym_mutex;

    void sendMessage(Message& msg, QTcpSocket *skt);

};


#endif //ES3_PROJ_NETWORKSERVER_SERVERTHREAD_H
