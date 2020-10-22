//
// Created by Windows on 14/08/2020.
//

#include "CursorPosition.h"

#include <utility>

CursorPosition::CursorPosition(Symbol& _s, qint32 index, qint32 siteID,QString& fileName) :
        s(_s), index(index), Payload(siteID),_fileName(fileName){}

CursorPosition::CursorPosition(Symbol& _s, qint32 index, qint32 siteID) : s(_s),index(index), Payload(siteID){}

qint32 CursorPosition::getIndex() const {
    return index;
}

Symbol CursorPosition::getSymbol() {
    return s;
}