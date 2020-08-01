//
// Created by utente on 03/11/2019.
//

#include <iostream>
#include <utility>
#include <QtCore/QDataStream>
#include <fstream>
#include <QtSql/QSqlDatabase>
#include <QtCore/QFile>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include "ServerThread.h"
#include "NetworkServer.h"
#include "Packet/LoginInfo.h"
#include "json/json.h"

std::shared_mutex ServerThread::skt_mutex;  // questo è lo shared mutex per la struttura "_sockets"
std::vector<std::pair<Socket*,std::mutex*>> ServerThread::_sockets; //qui ci sono dei mutex esclisivi per ogni socket
/// PER ORA USO IL VETTORE PER TESTARE IL FUNZIONAMENTO, POI INSERIRO' LA MAPPA (IL VETTORE SO USARLO BENE, LA MAPPA ANCORA NO)

ServerThread::ServerThread(qintptr socketDesc, MessageHandler *msgHandler,QObject *parent):QThread(parent){
    this->socketDescriptor = socketDesc;
    this->msgHandler = std::shared_ptr<MessageHandler>(msgHandler);
    this->_username = "";
    this->_siteID = -1;
}

void ServerThread::run()
{

    std::cout<<"ServerThread::run line 27, thread "<<std::this_thread::get_id()<<std::endl;

    socket = new Socket();
    socket->moveToThread(this);

    if ( !socket->setSocketDescriptor(this->socketDescriptor) )   //setto il descriptor del socket
    {
        emit error (socket->error());       //da gestire
        return;
    }

    connect(socket,&Socket::sendMessage,this,&ServerThread::sendPacket,Qt::QueuedConnection);
    connect(socket, SIGNAL(readyRead()), this, SLOT(recvPacket()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    setThreadId();
    QSqlDatabase::addDatabase("QSQLITE", threadId+"_login");
    QSqlDatabase::addDatabase("QSQLITE", threadId+"_directories");
    QSqlDatabase::addDatabase("QSQLITE", threadId+"_files");

    exec(); //loop degli eventi attivato qui
}

void ServerThread::recvPacket() {
    //std::cout << "Thread " << std::this_thread::get_id() << " reading from socket " << this->socketDescriptor<< std::endl;
    QDataStream in;
    qint32 bytes=0;
    qint32 source=0;
    quint32 errcode;
    quint32 type_of_data;

    //qDebug() << "Receving packet";

    in.setDevice(this->socket);
    in.setVersion(QDataStream::Qt_5_5);
    //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    while(this->socket->bytesAvailable()>0) {
        std::cout<<"--starting number of Available  Bytes: "<<socket->bytesAvailable()<<std::endl;
        if(this->socketSize==0) {
            in >> bytes;
            this->socketSize = bytes;
        }
        if(this->socketSize!=0 && bytes!=-14){
            if(socket->bytesAvailable()!=this->socketSize-4){
                return;
            }
        }

        in >> source>>errcode >> type_of_data;
        DataPacket packet(source, errcode, (DataPacket::data_t) type_of_data);

        switch (type_of_data) {
            case (DataPacket::login): {
                recvLoginInfo(packet, in);
                break;
            }

            case (DataPacket::textTyping): {
                recvMessage(packet, in);
                break;
            }

            case (DataPacket::command): {
                recvCommand(packet, in);
                break;
            }

            default: {
                std::cout << "Coglione c'è un errore" << std::endl;
                throw "mannaggia quel porcodiddio";
            }
        }
        std::cout<<"--ending number of Available Bytes: "<<socket->bytesAvailable()<<std::endl;
        std::cout<<std::endl;
        this->socketSize=0;
    }
}

void ServerThread::recvLoginInfo(DataPacket& packet, QDataStream& in) {
    quint32 siteId;
    qint32 type;
    QString user;
    QString password;

    in >> siteId >> type >> user >> password;

    if(type == LoginInfo::login_request && _username.isEmpty()) {
        auto shr = std::make_shared<LoginInfo>( -1, (LoginInfo::type_t)type, user, password);
        packet.setPayload(shr);
        _siteID = shr->login(threadId);
        if (_siteID != -1) {
            _username = user;
            std::cout << "client "+user.toStdString()+" successfully logged!" << std::endl;        //ATTUALMENTE se l'utente cerca di loggarsi ma è già loggato, il server
            sendPacket(packet);                                                                   //non fa nulla, non risponde con messaggi di errore
            {
                std::lock_guard lg(skt_mutex);
                _sockets.emplace_back(this->socket,new std::mutex());
            }
        } else {
            std::cout << "client not logged!" << std::endl;
            sendPacket(packet);
        }
    }
}

void ServerThread::recvMessage(DataPacket& packet,QDataStream& in)
{

    qint32 siteId;
    QString formattedMessages;

    in.setDevice(this->socket);
    in.setVersion(QDataStream::Qt_5_5);

    in >> siteId  >> formattedMessages;

    auto *strMess = new StringMessages(formattedMessages,siteId);
    packet.setPayload(std::shared_ptr<StringMessages>(strMess));

    //se l'utente non è loggato non deve poter inviare pacchetti con dentro Message
    //però potrebbe e in questo caso l'unico modo per pulire il socket è leggerlo
    if(!_username.isEmpty()) {

        for (auto msg: strMess->stringToMessages()) {
            if (msg.getAction() == Message::insertion) {
                msgHandler->submit(NetworkServer::localInsert, msg);
            } else {
                msgHandler->submit(NetworkServer::localErase, msg);
            }
        }

        /** nota: mentre la scrittura del file locale può essere una azione asincrona, la comunicazione
         * agli altri utenti di ciò che sta avvenendo non può per due motivi:
         * 1. è più urgente che i client sappiano cosa gli altri client stiano facendo piuttosto
         *    che sapere che quello che è stato scritto sia realmente stato salvato oppure no
         * 2. la comunicazione agli altri socket è probabilmente più rapida della scrittura
         *    su file.
         * inoltre in questo caso potrebbe essere utile uno shared_lock piuttosto che un lock in
         * mutua esclusione, questo perchè (verosimilmente) le azioni che richiedono l'accesso al
         * vettore di socket in scrittura saranno più rari e richiedono tempistiche molto più lunghe
         * (la scrittura su questo vettore avviene solo dopo la connessione di un client). Molto più
         * frequenti sono, invece, gli accessi in lettura; e non permettere ad un thread di leggere da
         * questo vettore quando un altro sta leggendo, è poco efficiente
        **/

        std::shared_lock sl(skt_mutex);
        for (auto skt: _sockets) {
            sl.unlock(); /// la presenza di questa roba è da testare, potrebbe non essere utile
            if (skt.first != socket) {
                int id = qMetaTypeId<DataPacket>();
                emit skt.first->sendMessage(packet,skt.second);
            }
            sl.lock();
        }
    }
}


void ServerThread::recvCommand(DataPacket &packet, QDataStream &in) {
    qint32 siteId;
    qint32 cmd;
    QVector<QString> args;

    in >> siteId >> cmd >> args;
    packet.setPayload(std::make_shared<Command>(siteId,(Command::cmd_t)cmd,std::move(args)));
    auto command = std::dynamic_pointer_cast<Command>(packet.getPayload());

    switch(cmd){
        case (Command::cd):{
            command->cdCommand(threadId, _username);
            sendPacket(packet);
            break;
        }

        case (Command::mkdir):{
            if(command->mkdirCommand(threadId, _username))
                std::cout << "mkdir command ok!" << std::endl;
            else
                std::cout << "mkdir command failed!" << std::endl;
            break;
        }

        case (Command::rm):{
            if(command->rmCommand(threadId, _username))
                std::cout << "rm command ok!" << std::endl;
            else
                std::cout << "mkdir command failed!" << std::endl;
            break;
        }

        case (Command::cp):{
            break;
        }

        case (Command::mv):{
            break;
        }

        case (Command::opn):{
            QString fileName;

            fileName = command->opnCommand(threadId, _username);
            if(!fileName.isEmpty())
                std::cout << fileName.toStdString() << std::endl;
            else
                std::cout << "opn command failed!" << std::endl;
            break;
        }

        case (Command::cls):{
            break;
        }

        default:
            std::cout << "Coglione errore nel Command" << std::endl;
    }
}

void ServerThread::sendPacket(DataPacket packet, std::mutex *mtx){

    std::cout<<"thread "<<std::this_thread::get_id()<<" sending packet to "<<this->socketDescriptor<<std::endl;

    switch(packet.getTypeOfData()){
        case (DataPacket::login): {
           sendLoginInfo(packet,mtx);
           break;
        }

        case (DataPacket::textTyping): {
            sendMessage(packet, mtx);
            break;
        }

        case (DataPacket::command): {
            sendCommand(packet, mtx);
            break;
        }

        default: {
            std::cout<<"Coglione c'è un errore"<<std::endl;
        }
    }
}

void ServerThread::sendLoginInfo(DataPacket &packet, std::mutex *mtx) {
    auto ptr = std::dynamic_pointer_cast<LoginInfo>(packet.getPayload());
    QDataStream out;
    out.setDevice(socket);
    out.setVersion(QDataStream::Qt_5_5);

    out << packet.getSource() << packet.getErrcode() << packet.getTypeOfData();
    out << ptr->getSiteId() << ptr->getType() << ptr->getUser() << ptr->getPassword();
    socket->waitForBytesWritten(-1);
}

void ServerThread::sendMessage(DataPacket& packet,std::mutex* mtx){

    QDataStream out;
    out.setDevice(socket);
    out.setVersion(QDataStream::Qt_5_5);

    auto strMess = std::dynamic_pointer_cast<StringMessages>(packet.getPayload());

    {
        std::lock_guard lg(*mtx);
        out << packet.getSource() << packet.getErrcode() << packet.getTypeOfData() <<
            strMess->getSiteId() << strMess->getFormattedMessages();
        socket->waitForBytesWritten(-1);
    }

}

void ServerThread::sendCommand(DataPacket& packet, std::mutex *mtx){
    QDataStream out;
    out.setDevice(socket);
    out.setVersion(QDataStream::Qt_5_5);

    auto ptr = std::dynamic_pointer_cast<Command>(packet.getPayload());
    out << packet.getSource() << packet.getErrcode() << packet.getTypeOfData();
    out << ptr->getSiteId() << (quint32) ptr->getCmd() << ptr->getArgs();
}

void ServerThread::QTsaveFileJson(const std::string& dir,std::vector<Symbol> _symbols){
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

void ServerThread::saveFileJson(std::string dir,std::vector<Symbol> _symbols){//vector<symbol> to json
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

std::vector<Symbol> ServerThread::loadFileJson(std::string dir){//json to vector<symbol>
    std::ifstream file_input(dir);
    Json::Reader reader;
    Json::Value root;
    reader.parse(file_input, root);

    std::vector<Symbol> _symbols;

    for(int i=0; i<root.size(); i++) {
        QChar value=*(root[i]["char"].asCString());
        qint32 _siteId=root[i]["symId"]["siteId"].asUInt64();
        qint32 _counter=root[i]["symId"]["count"].asUInt64();
        std::vector<quint32> pos;
        Symbol s(value,_siteId,_counter, pos);
        for(int j=0;j<root[i]["pos"].size();j++){
            qint32 val=root[i]["pos"][j].asUInt64();
            pos.push_back(val);
        }
        _symbols.insert(_symbols.end(),s);
    }
    return _symbols;
}

void ServerThread::disconnected()
{
    int i = 0;
    {
        std::shared_lock sl(skt_mutex);
        for (auto skt:_sockets) {
            if (skt.first == socket) break;
            i++;
        }
    }

    if(i<_sockets.size()){
        std::lock_guard lg(skt_mutex);
        _sockets.erase(_sockets.begin()+i);
    }

    socket->deleteLater();
    QSqlDatabase::removeDatabase(threadId+"_login");
    QSqlDatabase::removeDatabase(threadId+"_directories");
    QSqlDatabase::removeDatabase(threadId+"_files");
    std::cout<<"Client disconnected!"<<std::endl;
    exit(0);
}

void ServerThread::setThreadId() {
    auto myid = std::this_thread::get_id();
    std::stringstream ss;
    ss << myid;
    std::string IdString = ss.str();
    threadId = QString::fromStdString(IdString);
}
