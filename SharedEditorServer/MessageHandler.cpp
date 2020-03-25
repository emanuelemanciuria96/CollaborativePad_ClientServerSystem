//
// Created by utente on 22/03/2020.
//

#include "MessageHandler.h"
#include "NetworkServer.h"

void MessageHandler::startLooper() {
    std::unique_lock ul(mtx);
    while(!finished || !_queue.empty()){
        if(_queue.empty())
            cv.wait(ul); // mi metto in attesa della terminazione
        if(finished && _queue.empty())
            break;
        auto item = _queue.front();
        _queue.pop();

        ul.unlock();
        item.first(item.second);
        ul.lock();
    }
}

void MessageHandler::submit(std::function<void(Message)> f, Message& msg) {
    std::unique_lock ul(mtx);
    if(!finished)
        _queue.push(std::make_pair(f,msg));
    cv.notify_one();
}

MessageHandler::~MessageHandler() {
    {
        std::unique_lock ul(mtx);
        finished = true;
    }
    if(looper.joinable())
        looper.join();
}
