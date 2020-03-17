//
// Created by muska on 15/10/2019.
//

#ifndef ES3_PROJ_NETWORKSERVER_MESSAGE_H
#define ES3_PROJ_NETWORKSERVER_MESSAGE_H

#include "Payload.h"
#include "Symbols/Symbol.h"
#include <vector>
#include <QtGlobal>

typedef enum {insertion,removal} action_t;

class Message: public Payload {
private:
    action_t _action ;
    Symbol _sym;
public:
    Message(action_t action,qint32 siteId,Symbol& sym):
            _action(action), Payload(siteId), _sym(sym){}
    qint32 getSiteId(){ return _siteID; }
    action_t getAction() const{ return _action; }
    Symbol getSymbol() const{ return _sym; }
};


#endif //ES3_PROJ_NETWORKSERVER_MESSAGE_H
