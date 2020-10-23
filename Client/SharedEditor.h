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
#include "Packet/UserInfo.h"
#include "Packet/ErrorPacket.h"
#include <vector>
#include <algorithm>
#include <QtCore/QTimer>
#include <QIcon>
#include <QTextCharFormat>

class SharedEditor: public QObject {
    Q_OBJECT
private:
    qint32 _siteId;
    qint32 _counter;
    std::vector<Symbol> _symbols;
    Transceiver* transceiver;
    bool isLogged;
    QString fileOpened;
    bool isFileOpened;
    bool isArrivingFile;
    QString _user;
    bool highlighting;
    bool fileOpening = false;
    std::vector<std::vector<Message>> stackUndo;
    std::vector<std::vector<Message>> stackRedo;

    qint32 getIndex(qint32 index, Symbol symbol);
    void closeFile();
    void findCounter();

    void processMessages( StringMessages& strMess );
    void processLoginInfo( LoginInfo& logInf );
    void processFileInfo( FileInfo& filInf );
    void processUserInfo( UserInfo& userInfo);
    void processCommand( Command& cmd );
    void processLsCommand( Command& cmd );
    void processRenCommand( Command &cmd );
    void processLsInviteCommand( Command& cmd );
    void processInviteCommand( Command& cmd );
    void processFsNameCommand( Command& cmd );
    void processUriCommand( Command &cmd );
    void processRmCommand(Command &cmd );
    void processCursorPos(CursorPosition& curPos);
    void processErrorPacket(ErrorPacket& error);

public slots:
    void loginSlot(QString& username, QString& password);
    void process(DataPacket pkt);
    void requireFile(QString& fileName);
    void requireFileClose();
    void requireFileRename(const QString& before,const QString& after);
    void requireFileDelete(const QString& fileName);
    void requireFileAdd(const QString& fileName);
    void deleteThread();
    void clearText();
    void sendUpdatedInfo(const QPixmap& image, const QString& name, const QString& email);
    void sendRegisterRequest(QString& user, QString& password, QString& name, QString& email, QPixmap& image);
    void searchUser(const QString& user);
    void searchFsName(const QString& name);
    void submitInvite(const QString& file, const QString& user);
    void sendInviteAnswer(const QString& mode, const QString& user, const QString& filename);
    void submitUri(const QString& file);
    void obtainUser(qint32 siteId);
    void redo();
    void undo();
    void undoredoAction(){
        emit undoredoActionEnable(!stackUndo.empty(),!stackRedo.empty());
    }
    void clearUndoRedo(){
        stackUndo.clear();
        stackRedo.clear();
    }

signals:
    void hideEditor(QString& fileName);
    void openTextEditor(QString &fileName);
    void transparentForMouse();
    void symbolsChanged(qint32 pos, const QString& s, qint32 siteId, QTextCharFormat& format, Message::action_t action);
    void deleteAllText();
    void filePathsArrived(const QVector<QString>& paths);
    void fileNameEdited(QString& oldName, QString& newName);
    void fileDeletion(QString& fileName);
    void loginAchieved();
    void userInfoArrived(const QPixmap& image, const QString& nickname, const QString& name, const QString& email);
    void remoteCursorPosChanged(qint32 pos, qint32 siteId);
    void removeCursor(qint32 siteId);
    void highlight(qint32 pos, qint32 siteId);
    void searchUserResult(LoginInfo::type_t type);
    void loginError();
    void loginErrorAlreadyConn();
    void inviteListArrived(const QVector<QString> &args);
    void inviteResultArrived(const QString& result);
    void uriResultArrived(const QVector<QString> &args);
    void fsNameArrived(const QString& fsName);
    void setNumUsers(int n);
    void hideNumUsers();
    void returnToGrid();
    void addUser(UserInfo& user);
    void removeUser(UserInfo& user);
    void userNameArrived(qint32 siteId, QString& user, bool connected=false);
    void flushFileWriters();
    void setCharFormat(bool);
    void getAligment(short& a);
    void remoteAlignment(int pos, Qt::Alignment a );
    void usernameAlreadyExists();
    void serverUnavailable();
    void updateUserListInfo(const QPixmap& image, const QString& nickname, const QString& name, const QString& email);
    void errorArrived(const QString& message);
    void undoredoActionEnable(bool undo,bool redo);

public:
    explicit SharedEditor(QObject *parent = 0);
    void localInsert( qint32 index, QChar& ch, QTextCharFormat& format, Qt::Alignment align);
    void localErase( qint32 index, qint32 num);
    void localModification( qint32 index, QTextCharFormat& format );
    qint32 getSiteId() const;
    void sendCursorPos(qint32 index);
    void highlightSymbols(bool checked);
    bool getHighlighting() const;
    bool isFileOpening() const;
    void localAlignment(int pos, char a);

    const Symbol fromPosToSymbol(int pos){ return _symbols[pos]; }
    virtual ~SharedEditor();
    QVector<qint32> getSiteIds();
};


#endif //ES3_PROJ_SHAREDEDITOR_H
