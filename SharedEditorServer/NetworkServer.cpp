//
// Created by muska on 15/10/2019.
//
#include "NetworkServer.h"
#include <QApplication>


std::vector<Symbol> NetworkServer::_symbles;

NetworkServer::NetworkServer(QObject *parent) : QTcpServer(parent){
    msgHandler = std::make_shared<MessageHandler>();
}

void NetworkServer::startServer() {

    if(!this->listen(QHostAddress::Any, 1234))
    {
        qDebug() << "NetworkServer could not start!";
    }
    else
    {
        qDebug() << "NetworkServer started!";
    }

}

void NetworkServer::incomingConnection(qintptr socketDesc)
{

    qDebug() << "Client connected!";
    std::cout<<"NetworkServer::incomingConnection line 30, thread "<<std::this_thread::get_id()<<std::endl;
    qDebug()<< "Creating Thread";

    ServerThread *thread = new ServerThread(socketDesc,msgHandler.get());

    connect(thread,&ServerThread::deleteMe,this,&NetworkServer::deleteThread);
    connect(thread, &ServerThread::finished,
            [thread](){
                QPointer<QThread> th(thread);
                qRegisterMetaType<QPointer<QThread>>("QPointer<QThread>");
                emit thread->deleteMe(th);
            });

    thread->moveToThread(thread);

    thread->start();

}


void generateNewPosition( std::vector<qint32>& prev, std::vector<qint32>& next, std::vector<qint32>& newPos, qint32 depth = 0 ){

    quint32 pos;
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
    std::cout<<"thread "<<std::this_thread::get_id()<<" invoked localInsert"<<std::endl;
    int i = 0;
   // std::unique_lock ul(sym_mutex);
    for (auto s: _symbles) {   //algoritmo lineare, migliorabile
        if ( m.getSymbol() < s ) break;
        i++;
    }

    _symbles.insert(_symbles.begin() + i, m.getSymbol());

    to_string();
}

void NetworkServer::localErase(Message m) {
    std::cout<<"thread "<<std::this_thread::get_id()<<" invoked localErase"<<std::endl;
    int i = 0;
   // std::unique_lock ul(sym_mutex);
    for( auto s: _symbles){ //algoritmo lineare anche qui, migliorabile (penso che nella libreria STL ci possa essere già qualcosa di implementato)
        if( m.getSymbol() == s ) break;
            i++;
    }
    
    if(i<_symbles.size())
        _symbles.erase(_symbles.begin()+i);

    to_string();
}

void NetworkServer::to_string() {
    QString str;

    std::for_each(_symbles.begin(),_symbles.end(),
                  [&str](Symbol s){
                      str += s.getValue();
                  });
    std::cout<<"Local editor: "<<str.toStdString()<<std::endl;
}

void NetworkServer::deleteThread(QPointer<QThread> th) {
    auto thread = dynamic_cast<ServerThread*>(th.data());
    thread->deleteLater();
}
