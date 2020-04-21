//
// Created by tomma on 20/04/2020.
//

#include <iostream>
#include "StringMessages.h"

QString StringMessages::messageToString(Message& m){
    QString s="";
    if (m.getAction() == Message::insertion) {
        s="0";
    }else{
        s="1";
    }
    s.append(this->items_separator);
    s.append(m.getSymbol().getValue());
    s.append(this->items_separator);
    s.append(QString::number(m.getSymbol().getSymId().getSiteId()));
    s.append(this->items_separator);
    s.append(QString::number(m.getSymbol().getSymId().getCount()));
    s.append(this->items_separator);

    for(int i=0 ; i< m.getSymbol().getPos().size();i++){
        s.append(QString::number(m.getSymbol().getPos()[i]));
        s.append(this->pos_separator);
    }
    s.append(this->items_separator);
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
    splitString(vec_items,s,this->items_separator,this->items_separatorSize);

    QChar ch=QChar(vec_items[1].at(0));
    qint32 siteId=vec_items[2].toInt();
    qint32 count=vec_items[3].toInt();

    std::vector<quint32> pos;
    std::vector<QString> vec_pos;
    splitString(vec_pos,vec_items[4],this->pos_separator,this->pos_separatorSize);

    for(int i=0;i<vec_pos.size();i++){
        pos.push_back(vec_pos[i].toUInt());
    }
    Symbol sym(ch,siteId,count,pos);
    Message msg(vec_items[0] == "0" ? Message::insertion : Message::removal, siteId, sym);
    return msg;
}

void StringMessages::stringToMessages(QString str,std::vector<Message>& vm) {
    std::vector<QString> vec_messages;
    splitString(vec_messages, str, this->messages_separator, this->messages_separatorSize);
    for(int i=0;i<vec_messages.size();i++){
        vm.push_back(stringToMessage(vec_messages[i]));
    }
}

QString StringMessages::messagesToString(std::vector<Message> &vm) {
    QString str="";
    for (int i=0 ; i< vm.size();i++) {
        str.append(messageToString(vm[i]));
        str.append(this->messages_separator);
    }
    return str;
}



