//
// Created by utente on 03/11/2019.
//

#ifndef ES3_PROJ_NETWORKSERVER_SERVERTHREAD_H
#define ES3_PROJ_NETWORKSERVER_SERVERTHREAD_H

#include "Packet/DataPacket.h"
#include "Packet/StringMessages.h"
#include <QThread>
#include <QTcpSocket>
#include <QtCore/QMutex>
#include <shared_mutex>
#include "Packet/Symbols/Symbol.h"
#include "Packet/Message.h"
#include "Packet/LoginInfo.h"
#include "Packet/Command.h"
#include "MessageHandler.h"
#include "Socket.h"
#include "SocketsPool.h"
#include "Packet/CursorPosition.h"
#include "MyExceptions/LoginException.h"
#include "Packet/UserInfo.h"

class ServerThread : public QThread{
Q_OBJECT

public:
    explicit ServerThread(qintptr socketDesc, std::shared_ptr<MessageHandler> msgHandler,QObject *parent = 0);
    void run() override;
    void setFile(std::shared_ptr<std::vector<Symbol>> file) { _file = file; }
    QString getOperatingFileName(){ return operatingFileName; }
    qint32 getSiteID(){ return _siteID; }
    QString& getUsername(){ return _username; }
    std::shared_ptr<Socket> getSocket(){ return socket; }

signals:
    void error(QTcpSocket::SocketError socketerror);    //slot che gestisce questo segnale da implementare
    void deleteMe(QPointer<QThread> th);
    void recordThread(QPointer<QThread> th);

public slots:
    void recvPacket();
    void sendPacket(DataPacket packet);
    void sendFile();
    void sendPendentDelete(QString fileName);
    void flushQueue();
    void disconnected();

private:
    static std::shared_mutex db_op_mtx;
    std::shared_ptr<Socket> socket;
    qintptr socketDescriptor;
    std::shared_ptr<MessageHandler> msgHandler;
    std::shared_ptr<std::vector<Symbol>> _file;
    std::map<QString,QVector<qint32>> pendentDeleteList;

    static SocketsPool _sockets; // l'oggetto è thread safe
    QString _username;
    qint32 _siteID;
    QString threadId;
    QString operatingFileName;
    qint32 socketSize=0;
    bool isFileSent;
    std::queue<DataPacket> sendingQueue;

    void recvLoginInfo(DataPacket& packet, QDataStream& in);
    void recvMessage(DataPacket& packet,QDataStream& in);
    void recvCommand(DataPacket& packet,QDataStream& in);
    void recvCursorPos(DataPacket& packet, QDataStream& in);
    void recvUserInfo(DataPacket& packet, QDataStream& in);

    void sendLoginInfo(DataPacket& packet);
    void sendMessage(DataPacket& packet);
    void sendCommand(DataPacket& packet);
    void sendCursorPos(DataPacket& packet);
    void sendFileInfo(DataPacket& packet);
    void sendUserInfo(DataPacket& packet);
    void sendErrorPacket(DataPacket& packet);

    void setThreadId();

};


#endif //ES3_PROJ_NETWORKSERVER_SERVERTHREAD_H
