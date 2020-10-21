//
// Created by Muska on 21/10/2020.
//

#ifndef SHAREDEDITORSERVER_ERRORPACKET_H
#define SHAREDEDITORSERVER_ERRORPACKET_H


#include <QtCore/QString>
#include "Payload.h"

class ErrorPacket: public Payload {

private:
    QString message;
public:
    ErrorPacket(qint32 siteId, const QString &message);
    const QString &getMessage() const;
    void setMessage(const QString &message);
};


#endif //SHAREDEDITORSERVER_ERRORPACKET_H
