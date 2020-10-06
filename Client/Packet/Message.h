//
// Created by muska on 15/10/2019.
//

#ifndef ES3_PROJ_NETWORKSERVER_MESSAGE_H
#define ES3_PROJ_NETWORKSERVER_MESSAGE_H

#include "Payload.h"
#include "Symbols/Symbol.h"
#include <vector>
#include <QtGlobal>

class Message: public Payload {

public:
    typedef enum {insertion = 1,removal = 2} action_t;

    Message():Payload(-1),localIndex(-1),_sym(){}
    Message(action_t action,qint32 siteId,Symbol& sym,qint32 ind):
            _action(action), Payload(siteId), _sym(sym),localIndex(ind){}
    Message(const Message& msg) = default;
    qint32 getSiteId(){ return _siteID; }
    action_t getAction() const{ return _action; }
    Symbol getSymbol() const{ return _sym; }
    qint32 getLocalIndex(){ return localIndex; }
private:
    qint32 localIndex;
    action_t _action ;
    Symbol _sym;
};


#endif //ES3_PROJ_NETWORKSERVER_MESSAGE_H
