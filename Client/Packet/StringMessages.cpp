//
// Created by tomma on 20/04/2020.
//

#include <iostream>
#include "StringMessages.h"

StringMessages::StringMessages(std::vector<Message> &vm, qint32 siteID):Payload(siteID) {
    messagesToString(vm);
}

StringMessages::StringMessages(QString &stringMess,qint32 siteID):Payload(siteID) {
    formattedMessages = stringMess;
}

QString StringMessages::messageToString(Message& m){
    QString s="";
    if (m.getAction() == Message::insertion) {
        s="1";
    }else{
        s="2";
    }
    s.append(items_separator);
    s.append(m.getSymbol().getValue());
    s.append(items_separator);
    s.append(QString::number(m.getSymbol().getSymId().getSiteId()));
    s.append(items_separator);
    s.append(QString::number(m.getSymbol().getSymId().getCount()));
    s.append(items_separator);

    for(int i=0 ; i< m.getSymbol().getPos().size();i++){
        s.append(QString::number(m.getSymbol().getPos()[i]));
        s.append(pos_separator);
    }
    s.append(items_separator);
    return s;
}

void splitString(std::vector<QString>& vec, QString data, QString separator,int separatorSize){
    QString string=data;
    quint32 index=string.indexOf(separator);
    while(string.size()>separatorSize){
        vec.push_back(string.mid(0,index));
        string=string.mid(index+separatorSize);
        index=string.indexOf(separator);
    }
}

Message StringMessages::stringToMessage(QString s) {
    std::vector<QString> vec_items;
    splitString(vec_items,s,items_separator,items_separatorSize);

    QChar ch = QChar(vec_items[1].at(0));
    qint32 siteId=vec_items[2].toInt();
    qint32 count=vec_items[3].toInt();

    std::vector<quint32> pos;
    std::vector<QString> vec_pos;
    splitString(vec_pos,vec_items[4],pos_separator,pos_separatorSize);

    for(int i=0;i<vec_pos.size();i++){
        pos.push_back(vec_pos[i].toUInt());
    }
    Symbol sym(ch,siteId,count,pos);
    Message msg(vec_items[0] == "1" ? Message::insertion : Message::removal, siteId, sym);
    return msg;
}

std::vector<Message> StringMessages::stringToMessages() {
    std::vector<Message> vm;
    std::vector<QString> vec_messages;
    splitString(vec_messages, formattedMessages, messages_separator, messages_separatorSize);
    for(QString v: vec_messages){
        vm.push_back(stringToMessage(v));
    }
    return vm;
}

QString StringMessages::messagesToString(std::vector<Message> &vm) {
    formattedMessages = "";
    int index=0;
    for (auto m: vm) {
        index=index+1;
        formattedMessages.append(messageToString(m));
        formattedMessages.append(messages_separator);
        if(formattedMessages.size()>maxChar){
            break;
        }
    }

    vm.erase(vm.begin(), vm.begin() + index);
    return formattedMessages;
}

QString StringMessages::appendMessage(Message &m){
    formattedMessages.append(messageToString(m));
    formattedMessages.append(messages_separator);

    return formattedMessages;
}



