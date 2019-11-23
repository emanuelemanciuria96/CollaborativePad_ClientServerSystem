//
// Created by Emanuele on 23/08/2019.
//

#ifndef ES3_PROJ_SHAREDEDITOR_H
#define ES3_PROJ_SHAREDEDITOR_H

#include <iostream>
#include "Symbol.h"
#include <vector>
#include "Message.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QtCore/QDataStream>
#include <QAbstractSocket>
#include <QString>


class SharedEditor: public QObject {
private:
    qint32 _siteId;
    std::vector<Symbol> _symbols;
    qint32 _counter;
    QTcpSocket *socket;
    qint32 connectToServer();

private slots:
    void recvMessage();
    void sendMessage(Message& m);

public:
    explicit SharedEditor(QObject *parent = 0);
    void localInsert( qint32 index, QChar value );
    void localErase( qint32 index );
    void process( const Message& m);
    void to_string();

};


#endif //ES3_PROJ_SHAREDEDITOR_H
