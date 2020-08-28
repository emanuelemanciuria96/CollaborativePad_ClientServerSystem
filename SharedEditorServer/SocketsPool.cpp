//
// Created by utente on 04/08/2020.
//

#include <iostream>
#include "SocketsPool.h"

enum{mtx,sockets};

void SocketsPool::attachSocket(QString& fileName, qint32 siteId, Socket *skt) {

    std::unique_lock ul(skt_mtx);
    auto i = file_sockets.find(fileName);
    if( i!=file_sockets.end() ){
        std::unique_lock ul_skts(*std::get<mtx>(i->second));
        std::get<sockets>(i->second).insert(std::make_pair(siteId,skt));
    }
    else{
        std::map<qint32,Socket*> tmp = {{siteId,skt}};
        file_sockets.insert( std::make_pair(fileName,std::make_tuple(new std::shared_mutex(),tmp)) );
    }

}

void SocketsPool::detachSocket(QString &fileName, qint32 siteId) {

    std::shared_mutex* tmp = nullptr;

    std::unique_lock ul(skt_mtx);
    auto i = file_sockets.find(fileName);
    if( i!=file_sockets.end() ){
        std::unique_lock ul_skt(*std::get<mtx>(i->second));
        auto skt = std::get<sockets>(i->second).find(siteId);
        if( skt != std::get<sockets>(i->second).end() ){
            std::get<sockets>(i->second).erase(skt);
            if( std::get<sockets>(i->second).empty() ){
                tmp = std::get<mtx>(i->second);
                file_sockets.erase(i);
            }
        }
        else
            std::cout<<"qui non si dovrebbe mai arrivare! detachSocket"<<std::endl;
    }
    else
        std::cout<<"qui non si dovrebbe mai arrivare! detachSocket"<<std::endl;

    delete tmp;

}

void SocketsPool::broadcast(QString& fileName, qint32 siteId, DataPacket& pkt) {

    std::shared_lock sl(skt_mtx);
    auto i = file_sockets.find(fileName);
    if( i != file_sockets.end() ){
        std::shared_lock sl_skts(*std::get<mtx>(i->second) );
        for( auto skt : std::get<sockets>(i->second) ){
            if( skt.first != siteId ) {
                int id = qMetaTypeId<DataPacket>();
                emit skt.second->sendMessage(pkt);
            }
        }
    }
    else
        std::cout<<"qui non si dovrebbe mai arrivare! Broadcast"<<std::endl;

}








