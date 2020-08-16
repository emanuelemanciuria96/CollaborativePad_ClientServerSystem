//
// Created by Windows on 14/08/2020.
//

#include "CursorPosition.h"

CursorPosition::CursorPosition(qint32 pos, qint32 siteID) : pos(pos), Payload(siteID){}

quint32 CursorPosition::getPos() {
    return pos;
}