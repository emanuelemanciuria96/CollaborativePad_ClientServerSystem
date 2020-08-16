//
// Created by Windows on 14/08/2020.
//

#ifndef CLIENT_CURSORPOSITION_H
#define CLIENT_CURSORPOSITION_H

#include "Payload.h"

class CursorPosition : public Payload {
    quint32 pos;
public:
    CursorPosition(qint32 pos, qint32 siteID);
    quint32 getPos();
};


#endif //CLIENT_CURSORPOSITION_H
