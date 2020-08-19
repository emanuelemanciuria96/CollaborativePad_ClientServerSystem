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
#include "Packet/CursorPosition.h"
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
    qint32 getIndex(qint32 index, Symbol symbol);
    void processMessages(StringMessages& strMess);
    void processLoginInfo(LoginInfo& logInf);
    void processCommand(Command& cmd);
    void processCdCommand(Command& cmd);
    void processCursorPos(CursorPosition& curPos);
    bool isLogged;

public slots:
    void loginSlot(QString& username, QString& password);
    void process(DataPacket pkt);
    void deleteThread();
    void deleteText();

signals:
    void symbolsChanged(qint32 pos, const QString& s, qint32 siteId, Message::action_t action);
    void deleteAllText();
    void filePathsArrived(QVector<QString> &paths);
    void RemoteCursorPosChanged(qint32 pos, qint32 siteId);

public:
    explicit SharedEditor(QObject *parent = 0);
    void localInsert( qint32 index, QChar value );
    void localErase( qint32 index );
    QString to_string();
    void testCommand();
    qint32 getSiteId();
    void sendCursorPos(qint32 index);

};


#endif //ES3_PROJ_SHAREDEDITOR_H
