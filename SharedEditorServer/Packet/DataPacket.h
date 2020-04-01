//
// Created by utente on 17/03/2020.
//

#ifndef SHAREDEDITORSERVER_DATAPACKET_H
#define SHAREDEDITORSERVER_DATAPACKET_H

#include <QtGlobal>
#include <memory>
#include "Payload.h"

class DataPacket {
public:
    typedef enum Constants
    {
        textTyping = 0,
        login = 1,
        command = 2,
    }data_t;

    DataPacket(qint32 source, quint32 errcode, data_t typeOfData,Payload* pl= nullptr);
    qint32 getSource() const;
    void setSource(qint32 source);
    quint32 getErrcode() const;
    void setErrcode(quint32 errcode);
    quint32 getTypeOfData() const;
    void setTypeOfData(data_t typeOfData);
    std::shared_ptr<Payload> getPayload();
    void setPayload(std::shared_ptr<Payload> pl);
private:
    qint32 source;   //questo campo sarà riempito con il siteID nel caso in cui si conosca, -1 altrimenti
    quint32 errcode;
    data_t type_of_data;
    std::shared_ptr<Payload> payload;
};


#endif //SHAREDEDITORSERVER_DATAPACKET_H
