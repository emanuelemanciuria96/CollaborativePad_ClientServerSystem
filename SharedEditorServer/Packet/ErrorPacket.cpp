//
// Created by Muska on 21/10/2020.
//

#include "ErrorPacket.h"

ErrorPacket::ErrorPacket(qint32 siteId, const QString &message) : Payload(siteId), message(message) {}

const QString &ErrorPacket::getMessage() const {
    return message;
}

void ErrorPacket::setMessage(const QString &message) {
    ErrorPacket::message = message;
}
