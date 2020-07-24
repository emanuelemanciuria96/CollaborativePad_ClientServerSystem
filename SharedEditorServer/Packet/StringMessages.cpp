//
// Created by tomma on 20/04/2020.
//

#include <iostream>
#include "StringMessages.h"

StringMessages::StringMessages(std::vector<Message> &vm, qint32 siteID):Payload(siteID) {
    messages = std::make_shared<std::queue<Message>>();
    for(auto m : vm){
        messages.get()->push(m);
    }
}

Message StringMessages::pop() {
    auto m = messages.get()->front();
    messages.get()->pop();
    return m;
}

void StringMessages::push(Message &m) {
    messages.get()->push(m);
}

