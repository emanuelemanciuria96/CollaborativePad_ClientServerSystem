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
#include "Packet/CursorPosition.h"
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
    QString fileOpened = "";
    bool isFileOpened = false;
    bool highlighting = false;

    void findCounter();
    qint32 getIndex(qint32 index, Symbol symbol);

    void processMessages( StringMessages& strMess );
    void processLoginInfo( LoginInfo& logInf );
    void processFileInfo( FileInfo& filInf );
    void processCommand( Command& cmd );
    void processCdCommand( Command& cmd );
    void processLsCommand( Command& cmd );
    void processCursorPos(CursorPosition& curPos);


public slots:
    void loginSlot(QString& username, QString& password);
    void process(DataPacket pkt);
    void requireFileSystem();
    void requireFile(QString fileName);
    void deleteThread();
    void clearText();
    void sendUpdatedInfo(const QPixmap& image, const QString& name, const QString& email);

signals:
    void symbolsChanged(qint32 pos, const QString& s, qint32 siteId, Message::action_t action);
    void deleteAllText();
    void filePathsArrived(const QVector<QString> &paths);
    void loginAchieved();
    void userInfoArrived(const QPixmap& image, const QString& nickname, const QString& name, const QString& email);
    void remoteCursorPosChanged(qint32 pos, qint32 siteId);
    void removeCursor(qint32 siteId);
    void highlight(qint32 pos, qint32 siteId);
public:
    explicit SharedEditor(QObject *parent = 0);
    void localInsert( qint32 index, QChar value );
    void localErase( qint32 index );
    QString to_string();
    void testCommand();
    qint32 getSiteId();
    void sendCursorPos(qint32 index);
    void highlightSymbols(bool checked);
    bool getHighlighting();
};


#endif //ES3_PROJ_SHAREDEDITOR_H
