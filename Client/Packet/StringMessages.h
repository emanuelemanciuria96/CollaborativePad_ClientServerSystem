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
    // al momento è una classe a parte che espone due metodi per fare la conversione,
    // eventualmente possiamo integrare meglio questa classe come payload di un pacchetto
    // oppure sfruttare la command.
    //
    // la struttura della stringa è di questo tipo:
    //        0#&ch#&siteid#&count#&pos1,pos2,..,#&@%1#&ch#&siteid#&count...
    // il primo elemento può essere 0/1 a seconda se insertion/removal

    explicit StringMessages(qint32 siteID = -1):Payload(siteID){ messages = nullptr; }
    StringMessages(std::vector<Message> &vm, qint32 siteID);
    Message& pop();    
    void push(Message& m);
    std::shared_ptr<std::queue<Message>> getMessages(){ return messages; }
    
private:
    std::shared_ptr<std::queue<Message>> messages;

};

#endif //SHAREDEDITORSERVER_STRINGMESSAGES_H
