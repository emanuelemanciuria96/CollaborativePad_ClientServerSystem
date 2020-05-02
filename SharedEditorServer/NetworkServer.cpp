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
    thread->moveToThread(thread);

    connect(thread,&ServerThread::deleteMe,this,&NetworkServer::deleteThread);
    connect(thread, &ServerThread::finished,
            [thread](){
                QPointer<QThread> th(thread);
                qRegisterMetaType<QPointer<QThread>>("QPointer<QThread>");
                emit thread->deleteMe(th);
            });
    // adoperando una chiusura incapsulo il puntatore al thread, ciò mi permette di evitare
    // di costruirmi una struttura dati che mi tenga traccia di tutti i thread creati


    thread->start();

}


void NetworkServer::localInsert(Message m) {
    std::cout<<"thread "<<std::this_thread::get_id()<<" invoked localInsert"<<std::endl;

   // std::unique_lock ul(sym_mutex);
    auto i = std::lower_bound(_symbles.begin(),_symbles.end(),m.getSymbol());
    _symbles.insert(i,m.getSymbol());

    to_string();
}

void NetworkServer::localErase(Message m) {
    std::cout<<"thread "<<std::this_thread::get_id()<<" invoked localErase"<<std::endl;

   // std::unique_lock ul(sym_mutex);
    auto i = std::lower_bound(_symbles.begin(),_symbles.end(),m.getSymbol());

    if( *i == m.getSymbol() )  //l'oggetto va trovato per forza, se non c'è
        _symbles.erase(i);     //significa che non c'è coerenza fra i dati dei client

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
