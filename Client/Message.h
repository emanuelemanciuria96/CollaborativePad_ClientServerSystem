//
// Created by Emanuele on 23/08/2019.
//

#ifndef ES3_PROJ_MESSAGE_H
#define ES3_PROJ_MESSAGE_H

#include "Symbol.h"
#include <vector>
#include <QtGlobal>

typedef enum {insertion,removal} action_t;

class Message {
private:
    qint32 _siteID;
    action_t _action ;
    Symbol _sym;
public:
    Message(action_t action,qint32 siteId,Symbol& sym):
        _action(action), _siteID(siteId), _sym(sym){}
    qint32 getSiteId(){ return _siteID; }
    action_t getAction() const{ return _action; }
    Symbol getSymbol() const{ return _sym; }
};


#endif //ES3_PROJ_MESSAGE_H
