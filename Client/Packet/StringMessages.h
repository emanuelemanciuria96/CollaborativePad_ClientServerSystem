//
// Created by tomma on 20/04/2020.
//

#ifndef SHAREDEDITORSERVER_STRINGMESSAGES_H
#define SHAREDEDITORSERVER_STRINGMESSAGES_H

#include "Payload.h"
#include "Symbols/Symbol.h"
#include "Message.h"
#include <vector>
#include <QtGlobal>
#include <string>
#include <QString>
#include <queue>
#include <memory>


class StringMessages: public Payload{

public:

    explicit StringMessages(qint32 siteID = -1):Payload(siteID){  messages = std::make_shared<std::queue<Message>>();  }
    StringMessages(std::vector<Message> &vm, qint32 siteID);
    Message pop();
    void push(Message& m);
    std::shared_ptr<std::queue<Message>> getMessages(){ return messages; }
    
private:
    std::shared_ptr<std::queue<Message>> messages;

};

#endif //SHAREDEDITORSERVER_STRINGMESSAGES_H
