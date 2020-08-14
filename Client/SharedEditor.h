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
#include "Packet/FileInfo.h"
#include "Packet/LoginInfo.h"
#include "Packet/Command.h"
#include <vector>
#include <algorithm>
#include <QtCore/QTimer>


class SharedEditor: public QObject {
    Q_OBJECT
private:
    qint32 _siteId;
    qint32 _counter;
    std::vector<Symbol> _symbols;
    Transceiver* transceiver;
    bool isLogged;
    bool isFileOpened = false;

    qint32 getIndex( Message& m );
    void findCounter();

    void processMessages( StringMessages& strMess );
    void processLoginInfo( LoginInfo& logInf );
    void processFileInfo( FileInfo& filInf );
    void processCommand( Command& cmd );
    void processCdCommand( Command& cmd );
    void processTreeCommand( Command& cmd );


public slots:
    void loginSlot(QString& username, QString& password);
    void process(DataPacket pkt);
    void requireFileSystem();
    void requireFile(QString fileName);
    void deleteThread();
    void clearText();

signals:
    void symbolsChanged(qint32 pos, const QString& s, qint32 siteId, Message::action_t action);
    void deleteAllText();
    void filePathsArrived(const QVector<QString> &paths);
    void loginAchieved();

public:
    explicit SharedEditor(QObject *parent = 0);
    void localInsert( qint32 index, QChar value );
    void localErase( qint32 index );
    QString to_string();
    void testCommand();

};


#endif //ES3_PROJ_SHAREDEDITOR_H
