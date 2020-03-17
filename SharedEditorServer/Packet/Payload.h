//
// Created by utente on 17/03/2020.
//

#ifndef SHAREDEDITORSERVER_PAYLOAD_H
#define SHAREDEDITORSERVER_PAYLOAD_H

#include <QtGlobal>

class Payload {
protected:
    qint32 _siteID;
public:
    Payload(qint32 siteID):_siteID(siteID){}
};


#endif //SHAREDEDITORSERVER_PAYLOAD_H
