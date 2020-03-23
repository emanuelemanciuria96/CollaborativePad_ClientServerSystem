//
// Created by utente on 22/03/2020.
//

#include "MessageHandler.h"
#include "NetworkServer.h"

void MessageHandler::submit(std::function<void(Message)> f, Message msg) {
    _queue.push(std::make_pair(f,msg));
}

