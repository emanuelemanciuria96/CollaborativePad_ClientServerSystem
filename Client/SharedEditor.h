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
Q_OBJECT
private:
    qint32 _siteId;
    std::vector<Symbol> _symbols;
    qint32 _counter;
    QTcpSocket *socket;
    qint32 connectToServer();
    void recvMessage(QDataStream& in);
    void sendMessage(DataPacket& packet);
    void sendPacket(DataPacket& packet);
    void sendLoginInfo(DataPacket& packet);
    void recvLoginInfo(QDataStream& in);
    bool isLogged;

private slots:

    void recvPacket();

public slots:
    void loginSlot(QString& username, QString& password);

    void test();

signals:
    void symbolsChanged(qint32 pos, QChar value, qint32 siteId, Message::action_t action);

    void test1();

public:
    explicit SharedEditor(QObject *parent = 0);
    void localInsert( qint32 index, QChar value );
    void localErase( qint32 index );
    void process( const Message& m);
    QString to_string();

};


#endif //ES3_PROJ_SHAREDEDITOR_H
