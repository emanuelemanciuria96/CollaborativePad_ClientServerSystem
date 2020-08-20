//
// Created by Windows on 14/08/2020.
//

#ifndef CLIENT_CURSORPOSITION_H
#define CLIENT_CURSORPOSITION_H

#include "Symbols/Symbol.h"
#include "Payload.h"

class CursorPosition : public Payload {
    qint32 index;
    Symbol s;
public:
    CursorPosition(Symbol& _s, qint32 index, qint32 siteID);
    qint32 getIndex() const;
    Symbol getSymbol();
};


#endif //CLIENT_CURSORPOSITION_H
