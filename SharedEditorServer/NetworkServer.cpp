//
// Created by muska on 15/10/2019.
//
#include "NetworkServer.h"
#include <QtSql/QSqlDatabase>
#include <QApplication>
#include <QtCore/QBuffer>


std::vector<Symbol> NetworkServer::_symbles;
std::map<quint32,std::shared_ptr<Socket>> NetworkServer::active_sockets;
QString NetworkServer::threadId;

qint32 siteID = 0;

NetworkServer::NetworkServer(QObject *parent) : QTcpServer(parent){
    msgHandler = std::make_shared<MessageHandler>();

    setThreadId();
    QSqlDatabase::addDatabase("QSQLITE", threadId+"_login");
    QSqlDatabase::addDatabase("QSQLITE", threadId+"_directories");
    QSqlDatabase::addDatabase("QSQLITE", threadId+"_files");

    /*
    /// mi creo il json che mi serve
    std::vector<quint32> pos = {17};
    Symbol s1('c',8,10,pos);
    pos.push_back(12992);
    Symbol s2('i',8,19,pos);
    pos.push_back(92);
    Symbol s3('a',8,29,pos);
    pos.push_back(9928);
    Symbol s4('o',8,40,pos);
    std::vector<Symbol> syms = {s1,s2,s3,s4};
    saveFileJson(".\\prova.json",syms);
    */
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
    connect(thread,&ServerThread::recordThread,this,&NetworkServer::recordThread,Qt::QueuedConnection);

    thread->start();
}


void NetworkServer::localInsert(Payload &pl) {
    //std::cout<<"thread "<<std::this_thread::get_id()<<" invoked localInsert"<<std::endl;

    Message& m = dynamic_cast<Message&>(pl);
    // std::unique_lock ul(sym_mutex);
    auto i = std::lower_bound(_symbles.begin(),_symbles.end(),m.getSymbol());
    _symbles.insert(i,m.getSymbol());

    to_string();

}


void NetworkServer::localErase(Payload &pl) {
    //std::cout<<"thread "<<std::this_thread::get_id()<<" invoked localErase"<<std::endl;

    Message& m = dynamic_cast<Message&>(pl);
   // std::unique_lock ul(sym_mutex);
    auto i = std::lower_bound(_symbles.begin(),_symbles.end(),m.getSymbol());

    if( *i == m.getSymbol() )  //l'oggetto va trovato per forza, se non c'è
        _symbles.erase(i);     //significa che non c'è coerenza fra i dati dei client

    to_string();
}

void NetworkServer::processOpnCommand(Payload &pl) {

    Command& comm = dynamic_cast<Command&>(pl);

    QString filename = comm.getArgs().front();
    _symbles = loadFileJson(".\\"+filename.toStdString());

    std::vector<Message> vm;
    int index = 0;
    quint32 actualPacketDim = sizeof(quint32) + sizeof(qint32) + sizeof(DataPacket::data_t);

    for( auto s:_symbles){
        Message m(Message::insertion, siteID,s, index++);

        quint32 nextMessageSize = sizeof(m.getSiteId())+ sizeof(m.getAction())+ sizeof(m.getLocalIndex())+
                sizeof(m.getSymbol().getSymId())+ sizeof(m.getSymbol().getValue())+s.getPos().size()*sizeof(quint32);
        std::cout<<"next buffer size: "<<actualPacketDim+nextMessageSize<<std::endl;

        if( actualPacketDim+nextMessageSize >= 1000 ){
            DataPacket pkt(siteID,0,DataPacket::textTyping,new StringMessages(vm,siteID));
            int id = qMetaTypeId<DataPacket>();
            emit active_sockets.find(comm.getSiteId())->second->sendMessage(pkt);
            actualPacketDim = sizeof(quint32) + sizeof(qint32) + sizeof(DataPacket::data_t);
            vm.clear();
        }

        actualPacketDim+=nextMessageSize;
        vm.push_back(m);
    }
    if( !vm.empty() ){
        DataPacket pkt(siteID,0,DataPacket::textTyping,new StringMessages(vm,siteID));
        int id = qMetaTypeId<DataPacket>();
        emit active_sockets.find(comm.getSiteId())->second->sendMessage(pkt);
    }

}

/*
void NetworkServer::QTsaveFileJson(const std::string& dir,std::vector<Symbol> _symbols){
    QJsonArray symbols;

    for(auto& itr:_symbols) {
        QJsonObject symbol;
        QJsonObject symId;
        symbol["char"] = itr.getValue().toLatin1();
        symId["siteId"] = itr.getSymId().getSiteId();
        symId["count"] = itr.getSymId().getCount();
        symbol["symId"] = symId;
        QJsonArray pos;

        for(auto i: itr.getPos()){
            QJsonValue val((qint64)i);
            pos.append(val);
        }
        symbol["pos"]=pos;
        symbols.append(symbol);
    }
    QJsonDocument json(symbols);
    QFile file(QString::fromStdString(dir));
    file.open(QIODevice::WriteOnly);
    file.write(json.toJson());
}
*/

void NetworkServer::saveFileJson(std::string dir,std::vector<Symbol> _symbols){//vector<symbol> to json
    std::ofstream file_id;
    file_id.open(dir);
    Json::Value event;
    int index=0;
    for(auto itr:_symbols) {
        event[index]["index"] = index;
        event[index]["char"] = QString(itr.getValue()).toStdString();
        event[index]["symId"]["siteId"] = itr.getSymId().getSiteId();
        event[index]["symId"]["count"] = itr.getSymId().getCount();

        Json::Value vec(Json::arrayValue);

        for(int i=0; i<itr.getPos().size();i++){
            vec.append(Json::Value(itr.getPos()[i]));
        }
        event[index]["pos"]=vec;

        index++;
    }

    Json::StyledWriter styledWriter;
    file_id << styledWriter.write(event);

    file_id.close();
}

std::vector<Symbol> NetworkServer::loadFileJson(std::string dir){//json to vector<symbol>
    std::ifstream file_input(dir);
    Json::Reader reader;
    Json::Value root;
    reader.parse(file_input, root);

    std::vector<Symbol> symbles;

    for(int i=0; i<root.size(); i++) {
        QChar value=*(root[i]["char"].asCString());
        qint32 _siteId=root[i]["symId"]["siteId"].asUInt64();
        qint32 _counter=root[i]["symId"]["count"].asUInt64();
        std::vector<quint32> pos;
        for(int j=0;j<root[i]["pos"].size();j++){
            qint32 val=root[i]["pos"][j].asUInt64();
            pos.push_back(val);
        }
        Symbol s(value,_siteId,_counter, pos);
        symbles.insert(symbles.end(),s);
    }
    return symbles;
}

void NetworkServer::to_string() {
    QString str;

    std::for_each(_symbles.begin(),_symbles.end(),
                  [&str](Symbol s){
                      str += s.getValue();
                  });
    std::cout<<"Local editor: "<<str.toStdString()<<std::endl;
}

void NetworkServer::recordThread(QPointer<QThread> th) {
    auto thread = dynamic_cast<ServerThread*>(th.data());
    active_sockets.insert(std::make_pair(thread->getSiteID(),thread->getSocket()));
}

void NetworkServer::deleteThread(QPointer<QThread> th) {
    auto thread = dynamic_cast<ServerThread*>(th.data());
    auto i = active_sockets.find(thread->getSiteID());
    if( i != active_sockets.end() )
        active_sockets.erase(i);
    thread->deleteLater();
}

void NetworkServer::setThreadId() {
    auto myid = std::this_thread::get_id();
    std::stringstream ss;
    ss << myid;
    std::string IdString = ss.str();
    threadId = QString::fromStdString(IdString);
}

NetworkServer::~NetworkServer() {
    for(auto i:active_sockets)
        emit i.second->disconnected();
    active_sockets.clear();
}

