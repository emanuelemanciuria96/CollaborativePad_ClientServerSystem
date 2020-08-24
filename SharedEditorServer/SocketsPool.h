//
// Created by utente on 04/08/2020.
//

#ifndef SHAREDEDITORSERVER_SOCKETSPOOL_H
#define SHAREDEDITORSERVER_SOCKETSPOOL_H


#include <QtCore/QString>
#include <map>
#include "Socket.h"
#include <shared_mutex>

class SocketsPool {
public:
    SocketsPool() = default;
    void attachSocket(QString& fileName, qint32 siteId, std::shared_ptr<Socket> skt);
    void detachSocket(QString& fileName, qint32 siteId);
    void recordSocket(qint32 siteId, std::shared_ptr<Socket> skt);
    void discardSocket(qint32 siteId);
    void broadcast(QString& fileName, qint32 siteId, DataPacket& pkt);
    void broadcast( std::vector<qint32> &siteId_list, DataPacket& pkt );

private:
    std::shared_mutex fskt_mtx;
    std::map< QString,std::tuple<std::shared_mutex*, std::map< qint32,std::shared_ptr<Socket> > > > file_sockets;
    std::shared_mutex skt_mtx;
    std::map<qint32,std::shared_ptr<Socket> > online_sockets;

};


#endif //SHAREDEDITORSERVER_SOCKETSPOOL_H
