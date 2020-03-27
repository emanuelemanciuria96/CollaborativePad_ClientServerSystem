//
// Created by Emanuele on 23/08/2019.
//

#ifndef ES3_PROJ_SHAREDEDITOR_H
#define ES3_PROJ_SHAREDEDITOR_H

#include <iostream>
#include "Packet/Symbols/Symbol.h"
#include <vector>
#include "Packet/DataPacket.h"
#include "Packet/Payload.h"
#include "Packet/Message.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QtCore/QDataStream>
#include <QAbstractSocket>
#include <QString>


class SharedEditor: public QObject {
private:
    qint32 _siteId;
    std::vector<Symbol> _symbols;
    qint32 _counter;
    QTcpSocket *socket;
    qint32 connectToServer();
    void sendPacket(DataPacket& packet);
    bool isLogged;

private slots:
    void recvMessage();
    void sendMessage(DataPacket& packet);
    void recvPacket();

public slots:
    void login(QString& username, QString& password);

public:
    explicit SharedEditor(QObject *parent = 0);
    void localInsert( qint32 index, QChar value );
    void localErase( qint32 index );
    void process( const Message& m);
    void to_string();

};


#endif //ES3_PROJ_SHAREDEDITOR_H
