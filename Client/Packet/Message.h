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
    typedef enum {insertion = 0,removal = 1} action_t;

    Message(action_t action,qint32 siteId,Symbol& sym):
            _action(action), Payload(siteId), _sym(sym){}
    Message(const Message& msg) = default;
    qint32 getSiteId(){ return _siteID; }
    action_t getAction() const{ return _action; }
    Symbol getSymbol() const{ return _sym; }
private:
    action_t _action ;
    Symbol _sym;
};


#endif //ES3_PROJ_NETWORKSERVER_MESSAGE_H
