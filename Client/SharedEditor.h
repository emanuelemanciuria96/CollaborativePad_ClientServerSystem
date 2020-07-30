//
// Created by Emanuele on 23/08/2019.
//

#ifndef ES3_PROJ_SHAREDEDITOR_H
#define ES3_PROJ_SHAREDEDITOR_H

#include <iostream>
#include "Packet/Symbols/Symbol.h"
#include <vector>
#include "Packet/StringMessages.h"
#include "Packet/DataPacket.h"
#include "Packet/Payload.h"
#include "Socket.h"
#include "Transceiver.h"
#include "Packet/Message.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QtCore/QDataStream>
#include <QAbstractSocket>
#include <QString>

#include "Packet/LoginInfo.h"
#include "Packet/Command.h"
#include <vector>
#include <algorithm>
#include <QtCore/QTimer>


class SharedEditor: public QObject {
    Q_OBJECT
private:
    qint32 _siteId;
    std::vector<Symbol> _symbols;
    qint32 _counter;
    Transceiver* transceiver;
    qint32 getIndex(Message& m);
    void processMessages(StringMessages& strMess);
    void processLoginInfo(LoginInfo& logInf);
    void processCommand(Command& cmd);
    void processCdCommand(Command& cmd);
    bool isLogged;

public slots:
    void loginSlot(QString& username, QString& password);
    void process(DataPacket pkt);
    void deleteThread();
    void deleteText();

signals:
    void symbolsChanged(qint32 pos, const QString& s, qint32 siteId, Message::action_t action);
    void deleteAllText();

public:
    explicit SharedEditor(QObject *parent = 0);
    void localInsert( qint32 index, QChar value );
    void localErase( qint32 index );
    QString to_string();
    void testCommand();

};


#endif //ES3_PROJ_SHAREDEDITOR_H
