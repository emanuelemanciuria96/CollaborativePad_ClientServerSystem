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



class StringMessages{

public:
    // al momento è una classe a parte che espone due metodi per fare la conversione,
    // eventualmente possiamo integrare meglio questa classe come payload di un pacchetto
    // oppure sfruttare la command.
    //
    // la struttura della stringa è di questo tipo:
    //        0#&ch#&siteid#&count#&pos1,pos2,..,#&@%1#&ch#&siteid#&count...
    // il primo elemento può essere 0/1 a seconda se insertion/removal

    void stringToMessages(QString str,std::vector<Message> &vm);  // string to message vector
    QString messagesToString(std::vector<Message> &vm); // message vector to string

private:
    QString messageToString(Message& m); // functions for
    Message stringToMessage(QString s);  //      single message

    const QString messages_separator="@%";   // separatore dei messaggi
    const QString items_separator="#&";    //  separatore di elementi del messaggio
    const QString pos_separator=",";       //  separatore degli elementi del pos di un messaggio

    const int messages_separatorSize=messages_separator.size();
    const int items_separatorSize=items_separator.size();
    const int pos_separatorSize=pos_separator.size();
};

#endif //SHAREDEDITORSERVER_STRINGMESSAGES_H
