//
// Created by muska on 15/10/2019.
//
#include "NetworkServer.h"
#include <QApplication>



NetworkServer::NetworkServer(QObject *parent) : QTcpServer(parent){}

void NetworkServer::startServer() {

    if(!this->listen(QHostAddress::Any, 1234))
    {
        qDebug() << "NetworkServer could not start!";
    }
    else
    {
        qDebug() << "NetworkServer started!";
    }

    msgHandler = MessageHandler();

}

void NetworkServer::incomingConnection(qintptr socketDesc)
{

    qDebug() << "Client connected!";
    std::cout<<std::this_thread::get_id()<<std::endl;
    qDebug()<< "Creating Thread";

    ServerThread *thread = new ServerThread(socketDesc,&msgHandler,&sym_mutex,&_symbols,&skt_mutex,&_sockets,this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();

}


void generateNewPosition( std::vector<qint32>& prev, std::vector<qint32>& next, std::vector<qint32>& newPos, qint32 depth = 0 ){

    qint32 pos;
    if ( depth >= prev.size() ){
        prev.push_back(0);
    }
    if( depth >= next.size() ){
        next.push_back(INT_MAX);
    }
    if( next[depth] - prev[depth] > 1 ){
        pos = (float)prev[depth]/2 + (float)next[depth]/2;
    }
    else if ( next[depth] - prev[depth] <= 1 ){
        pos = prev[depth];
        generateNewPosition(prev, next, newPos, depth+1);
    }
    newPos.insert(newPos.begin(),pos);

}

void NetworkServer::localInsert(Message m) {
    std::cout<<"localInsert invoked"<<std::endl;
}

void NetworkServer::to_string() {
    QString str;

    std::for_each(_symbols.begin(),_symbols.end(),
                  [&str](Symbol s){
                      str += s.getValue();
                  });
    std::cout<<"Local editor: "<<str.toStdString()<<std::endl;
}
