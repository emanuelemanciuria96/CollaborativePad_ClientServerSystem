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
#include <QVector>


class StringMessages: public Payload{

public:
    explicit StringMessages(qint32 siteID):Payload(siteID){}
    StringMessages(std::vector<Message> &vm, qint32 siteID, QString& file);

    int storeQueue(std::vector<Message> &vm);
    const QVector<Message>& getQueue(){ return _messages; }
    void clearQueue(){ _messages.clear(); }
    QVector<Message>&& takeQueue(){ return std::move(_messages); }
    void appendMessage(Message &m);
    int size(){ return _messages.size(); }
    QString getFileName(){ return _fileName; }
    void setFileName(QString& file){ _fileName=file; }

private:
    const int maxDim=200;
    QString _fileName;
    QVector<Message> _messages;

};

#endif //SHAREDEDITORSERVER_STRINGMESSAGES_H
