//
// Created by utente on 17/03/2020.
//

#ifndef SHAREDEDITORSERVER_DATAPACKET_H
#define SHAREDEDITORSERVER_DATAPACKET_H

#include <QtGlobal>
#include <memory>
#include "Payload.h"

class DataPacket {
private:
    qint32 source;   //questo campo sarà riempito con il siteID nel caso in cui si conosca, -1 altrimenti
    quint32 errcode;
    quint32 type_of_data;
    std::unique_ptr<Payload> payload;
public:
    static const quint32 textTyping;
    static const quint32 login;
    static const quint32 idResponse;
};


#endif //SHAREDEDITORSERVER_DATAPACKET_H
