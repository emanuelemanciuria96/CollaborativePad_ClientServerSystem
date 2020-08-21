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
#include "MessageHandler.h"
#include "Socket.h"
#include "Files.h"
#include "Packet/FileInfo.h"
#include <QtCore/QPointer>
#include <QtCore/QTimer>

class NetworkServer: public QTcpServer{
Q_OBJECT
public:
    explicit NetworkServer(QObject *parent = 0);
    NetworkServer(const NetworkServer& ns) = delete;
    ~NetworkServer();
    void startServer();

    static void localInsert(Payload &pl);
    static void localErase(Payload &pl);
    static void processOpnCommand(Payload &pl);
    static void processClsCommand(Payload &pl);

public slots:
    void deleteThread(QPointer<QThread> th);
    void recordThread(QPointer<QThread> th);
    void saveAllFiles();

private:
    std::shared_ptr<MessageHandler> msgHandler;
    static Files files;
    static std::map<quint32,std::shared_ptr<ServerThread>> active_threads;
    static QString threadId;
    static QTimer *timer;

    static std::atomic<bool> fileOpened;

    void setThreadId();
    static std::shared_mutex sym_mutex;


    static void show_file(QString& fileName);
    static QString to_string(std::vector<Symbol> symbles);

protected:
    void incomingConnection(qintptr socketDesc) Q_DECL_OVERRIDE;

};


#endif //ES3_PROJ_NETWORKSERVER_NETWORKSERVER_H
