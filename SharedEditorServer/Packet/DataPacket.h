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
    std::shared_ptr<Payload> payload;

public:
    DataPacket(qint32 source, quint32 errcode, quint32 typeOfData);
    qint32 getSource() const;
    void setSource(qint32 source);
    quint32 getErrcode() const;
    void setErrcode(quint32 errcode);
    quint32 getTypeOfData() const;
    void setTypeOfData(quint32 typeOfData);
    std::shared_ptr<Payload>& getPayload();

    enum Constants
    {
        textTyping = 0,
        login = 1,
        idResponse = 2,
    };
};


#endif //SHAREDEDITORSERVER_DATAPACKET_H
