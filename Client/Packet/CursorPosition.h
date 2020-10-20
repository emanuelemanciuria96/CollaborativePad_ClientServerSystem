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
    QString _fileName;
public:
    CursorPosition(Symbol& _s, qint32 index, qint32 siteID, QString& fileName);
    CursorPosition(Symbol& _s, qint32 index, qint32 siteID);
    qint32 getIndex() const;
    Symbol getSymbol();
    void setFileName( QString& fileName){ _fileName = fileName; }
    QString getFileName(){ return _fileName; }
};


#endif //CLIENT_CURSORPOSITION_H
