//
// Created by muska on 15/10/2019.
//
#include "NetworkServer.h"
#include <QtSql/QSqlDatabase>
#include <QApplication>
#include <QtCore/QBuffer>
#include "MyExceptions/LoginException.h"


Files NetworkServer::files;
std::map<quint32,std::shared_ptr<ServerThread>> NetworkServer::active_threads;
QString NetworkServer::threadId;
QTimer *NetworkServer::timer;
std::atomic<bool> NetworkServer::fileOpened = false;

qint32 siteID = 0;

NetworkServer::NetworkServer(QObject *parent) : QTcpServer(parent){
    msgHandler = std::make_shared<MessageHandler>();


    setThreadId();
    QSqlDatabase::addDatabase("QSQLITE", threadId+"_login");
    QSqlDatabase::addDatabase("QSQLITE", threadId+"_directories");
    QSqlDatabase::addDatabase("QSQLITE", threadId+"_files");

    timer = new QTimer();
    timer->setSingleShot(true);
    connect(timer,SIGNAL(timeout()),this,SLOT(saveAllFiles()));

    timer->start(60000);

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

    ServerThread *thread = new ServerThread(socketDesc,msgHandler);
    thread->moveToThread(thread);

    connect(thread,&ServerThread::deleteMe,this,&NetworkServer::deleteThread);
    connect(thread, &ServerThread::finished,
            [thread](){
                QPointer<QThread> th(thread);
                qRegisterMetaType<QPointer<QThread>>("QPointer<QThread>");
                emit thread->deleteMe(th);
            });
    // adoperando una chiusura incapsulo il puntatore al thread
    connect(thread,&ServerThread::recordThread,this,&NetworkServer::recordThread,Qt::DirectConnection);

    thread->start();
}


void NetworkServer::localInsert(Payload &pl) {
    //std::cout<<"thread "<<std::this_thread::get_id()<<" invoked localInsert"<<std::endl;

    Message& m = dynamic_cast<Message&>(pl);
    Symbol sym = m.getSymbol();
    QString fileName = active_threads.find(m.getSiteId())->second->getOperatingFileName();
    if( fileName != "" ) {
        files.addSymbolInFile(fileName, sym);
        //show_file(fileName);
    }

}

void NetworkServer::localErase(Payload &pl) {
    //std::cout<<"thread "<<std::this_thread::get_id()<<" invoked localErase"<<std::endl;

    Message& m = dynamic_cast<Message&>(pl);
    Symbol sym = m.getSymbol();
    QString fileName = active_threads.find(m.getSiteId())->second->getOperatingFileName();
    if( fileName != "" ) {
        files.rmvSymbolInFile(fileName, sym);
        //show_file(fileName);
    }

}


void NetworkServer::processOpnCommand(Payload &pl) {

    Command& comm = dynamic_cast<Command&>(pl);
    QString fileName = comm.getArgs().front();

    std::cout<<"opening file: "<<fileName.toStdString()<<std::endl;

    std::vector<Symbol> symbles(files.openFile(fileName));

    auto th = active_threads.find(comm.getSiteId());
    if(th != active_threads.end()){
        th->second->setFile(std::move(symbles));
        emit th->second->getSocket()->sendFile();

        fileOpened.store(true);
    }

}

void NetworkServer::processClsCommand(Payload &pl) {

    Command &comm = dynamic_cast<Command &>(pl);
    QString fileName = comm.getArgs().front();

    std::cout<<"closing file: "<<fileName.toStdString()<<std::endl;

    files.closeFile(fileName);


}

void NetworkServer::processRmCommand(Payload &pl) {

    Command &comm = dynamic_cast<Command &>(pl);
    QString fileName = comm.getArgs().last();

    files.deleteFile(fileName);

    std::cout<<"deleting file: "+fileName.toStdString()<<std::endl;

    fileName = comm.getArgs().first();
    auto th = active_threads.find(comm.getSiteId());
    if(th != active_threads.end())
        emit th->second->getSocket()->sendPendentDelete(fileName);

}

void NetworkServer::saveAllFiles() {
    if( fileOpened.load() ) {
        std::cout<<"saving files"<<std::endl;
        files.saveAll();
    }
    timer->start(60000);
}

void NetworkServer::recordThread(QPointer<QThread> th) {
    auto thread = dynamic_cast<ServerThread*>(th.data());
    if( active_threads.find(thread->getSiteID()) != active_threads.end() )
        throw LoginException("User already logged !");

    std::shared_ptr<ServerThread> thread_ptr(thread,[](ServerThread *thread){ thread -> deleteLater(); }); // è necessario ridefinire il distruttore per il tipo ServerThread
    active_threads.insert(std::make_pair(thread->getSiteID(),thread_ptr));
}

void NetworkServer::deleteThread(QPointer<QThread> th) {
    auto thread = dynamic_cast<ServerThread*>(th.data());
    
    auto i = active_threads.find(thread->getSiteID());
    if( i != active_threads.end() )
        active_threads.erase(i);
}

void NetworkServer::setThreadId() {
    auto myid = std::this_thread::get_id();
    std::stringstream ss;
    ss << myid;
    std::string IdString = ss.str();
    threadId = QString::fromStdString(IdString);
}


NetworkServer::~NetworkServer() {
    timer->deleteLater();
    for(auto i:active_threads)
        emit i.second->getSocket()->disconnected();
    active_threads.clear();
}

