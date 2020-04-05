//
// Created by utente on 03/11/2019.
//

#include <iostream>
#include <utility>
#include <QtCore/QDataStream>
#include <fstream>
#include "ServerThread.h"
#include "NetworkServer.h"
#include "Packet/LoginInfo.h"
#include "json/json.h"

/**
 *  per quanto riguarda la classe ServerThread
 *  preferirei non avere questa infinità di parametri da passare
 *  ad ogni creazione. Inoltre non sono troppo convinto di voler
 *  usare tutti questi puntatori, potrebbero portare a fare qualche
 *  danno nella gestione della memoria. Una possibile soluzione
 *  sarebbe salvarsi direttamente il parent ed accedere ad i suoi
 *  campi attraverso metodi di tipo get/set ma equivale praticamente
 *  ad impostare come pubbliche tutte queste struttutre. Oppure salvarsi
 *  in ogni caso tutti i puntatori che servono, ma in maniera sicura,
 *  utilizzando smartptr
 **/

std::shared_mutex ServerThread::skt_mutex;  // questo è lo shared mutex per la struttura "_sockets"
std::vector<std::pair<QTcpSocket*,std::mutex*>> ServerThread::_sockets; //qui ci sono dei mutex esclisivi per ogni socket
/// PER ORA USO IL VETTORE PER TESTARE IL FUNZIONAMENTO, POI INSERIRO' LA MAPPA (IL VETTORE SO USARLO BENE, LA MAPPA ANCORA NO)

ServerThread::ServerThread(qintptr socketDescriptor, MessageHandler *msgHandler,QObject *parent):QThread(parent){
    this->socketDescriptor = socketDescriptor;
    this->msgHandler = msgHandler;
    this->isLogged = false;
}

void ServerThread::run()
{
    socket = new QTcpSocket();

    if ( !socket->setSocketDescriptor(this->socketDescriptor) )   //setto il descriptor del socket
    {
        emit error (socket->error());         //da gestire
        return;
    }

    {
        std::lock_guard lg(skt_mutex);
        _sockets.emplace_back(socket,new std::mutex());
    }
    connect(socket, SIGNAL(readyRead()), this, SLOT(recvPacket()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    std::cout<<"readyRead signal set!"<<std::endl;

    exec(); //loop degli eventi attivato qui
}

/** da modificare nella funzione readyRead:
 *      - per ogni casistica di "action" sarebbe preferibile inserire
 *        una chiamata a funzione per alleggerire la lettura del codice
 *      - sarebbe preferibile utilizzare una ricerca dicotomica sulla
 *        posizione (chiave di ordinamento del vettore) oppure, qualora
 *        possibile, cercare un contenitore dell'STL che sia adatto alla
 *        ricerca (che implementi già algoritmi di ricerca ottimi)
 *      - probabilmente, in implementazioni future, sarebbe meglio
 *        che il thread che parla con il client gestisca solamente
 *        i messaggi, senza interferire con la scrittura del vettore
 *        dei simboli. L'idea è quella di far inserire a questo thread
 *        il messaggio ricevuto in una coda di messaggi (quindi O(1))
 *        e lasciare l'inserimento ( potenzialmente O(log(n)) ) ad un
 *        "terzo" thread che avrà il solo compito di svuotare la coda
 *        e gestirsi il vettore di simboli. A livello computazionale questa soluzione
 *        è molto più leggera, dal momento che un singolo thread tiene
 *        occupata una sola struttura (la coda) per un tempo molto breve,
 *        l'implementazine attuale, invece, prevede che il thread mantenga
 *        occupata la struttura del testo ( _symbols ) per un tempo
 *        potenzialmente molto lungo.
 **/

void ServerThread::recvPacket()
{
    std::cout<<std::this_thread::get_id()<<" reading from socket "<<this->socketDescriptor<<std::endl;

    QDataStream in;
    qint32 source;
    quint32 errcode;
    quint32 type_of_data;

    qDebug()<<"Receving packet";

    in.setDevice(this->socket);
    in.setVersion(QDataStream::Qt_5_5);

    in >> source >> errcode >> type_of_data;
    DataPacket packet(source, errcode, type_of_data);

    switch (type_of_data){
        case (DataPacket::login): {
            quint32 siteId;
            qint32 type;
            QString user;
            QString password;

            in >> siteId >> type >> user >> password;

            if(type == LoginInfo::login_request && !isLogged) {
                packet.getPayload() = std::make_shared<LoginInfo>(LoginInfo(-1, type, std::move(user), std::move(password)));
                if (login(packet) != -1) {
                    std::cout << "client successfully logged!" << std::endl;
                    isLogged = true;                                               //ATTUALMENTE se l'utente cerca di loggarsi ma è già loggato, il server
                    sendPacket(packet, this->socket);                           //non fa nulla, non risponde con messaggi di errore
                } else
                    std::cout << "client not logged!" << std::endl;
                    sendPacket(packet, this->socket);
            }

            break;
        }

        case (DataPacket::textTyping): {
            recvMessage(packet);
            break;
        }

        default: {
            std::cout<<"Coglione c'è un errore"<<std::endl;
        }
    }
}

void ServerThread::recvMessage(DataPacket& packet)
{
    std::cout<<"thread "<<std::this_thread::get_id()<<" reading from socket "<<this->socketDescriptor<<std::endl;

    QDataStream in;
    qint32 siteIdM;
    qint32 action;
    QChar ch;
    qint32 siteIdS;
    quint32  count;
    qint32 num;
    qint32 p;
    std::vector<quint32> pos;

    qDebug()<<"Receving message";

    in.setDevice(this->socket);
    in.setVersion(QDataStream::Qt_5_5);

    in >> siteIdM >> action >> ch >> siteIdS >> count >> num; //il protocollo scelto per il passaggio della posizione richiede
    for(int i=0; i<num; i++){                                 //la lettura di un valore ad indicare la lunghezza di pos
        in >> p;
        pos.push_back(p);
    }

    if(isLogged) {                                          //se l'utente non è loggato non deve poter inviare pacchetti con dentro Message
        Symbol sym(ch, siteIdS, count, pos);            //però potrebbe e in questo caso l'unico modo per pulire il socket è leggerlo
        packet.getPayload() = std::make_shared<Message>(Message((Message::action_t) action, siteIdM, sym));
        auto msg = *std::dynamic_pointer_cast<Message>(packet.getPayload());

        //Message msg((action_t) action, siteIdM, sym);
        if (action == Message::insertion) {
            msgHandler->submit(NetworkServer::localInsert, msg);
        } else {
            msgHandler->submit(NetworkServer::localErase, msg);
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
            sl.unlock();
            if (skt.first != socket) {
                sendPacket(packet, skt.first, skt.second);
            }
            sl.lock();
        }
    }
}

void ServerThread::sendPacket(DataPacket& packet, QTcpSocket *skt, std::mutex *mtx){
    switch(packet.getTypeOfData()){
        case (DataPacket::login): {
            auto ptr = std::dynamic_pointer_cast<LoginInfo>(packet.getPayload());
            QDataStream out;
            out.setDevice(skt);
            out.setVersion(QDataStream::Qt_5_5);

            out << packet.getSource() << packet.getErrcode() << packet.getTypeOfData();
            out << ptr->getSiteId() << ptr->getType() << ptr->getUser() << ptr->getPassword();
            skt->waitForBytesWritten(-1);
            break;
        }

        case (DataPacket::textTyping): {
            sendMessage(packet, skt, mtx);
            break;
        }

        default: {
            std::cout<<"Coglione c'è un errore"<<std::endl;
        }
    }
}

void ServerThread::sendMessage(DataPacket& packet, QTcpSocket *skt,std::mutex* mtx) {
    QDataStream out;
    out.setDevice(skt);
    out.setVersion(QDataStream::Qt_5_5);

    auto msg = std::dynamic_pointer_cast<Message>(packet.getPayload());
    qint32 num=msg->getSymbol().getPos().size();


    {
        std::lock_guard lg(*mtx);
        out << packet.getSource() << packet.getErrcode() << packet.getTypeOfData();
        out << msg->getSiteId() << (qint32)msg->getAction() << msg->getSymbol().getValue() << msg->getSymbol().getSymId().getSiteId() << msg->getSymbol().getSymId().getCount() << num;
        for(auto i : msg->getSymbol().getPos())
            out << (qint32) i;
        skt->waitForBytesWritten(-1);
    }
}

qint32 ServerThread::login(DataPacket& packet) {
    auto ptr = std::dynamic_pointer_cast<LoginInfo>(packet.getPayload());
    LoginInfo logData = loadLoginJson(ptr->getUser().toStdString()+".json");
    if(ptr->getUser() == logData.getUser() && ptr->getPassword() == logData.getPassword()) {
        ptr->setType( LoginInfo::login_ok);
        ptr->setSiteId(5);
        ptr->setUser("");
        ptr->setPassword("");

//        QString str = "ciaost";
//        qint32 _counter = 0;hb8u
//        for(int i=1;i<7;i++){
//            std::vector<quint32> newPos;
//            Symbol s(str[i-1],10,_counter++,newPos);
////            std::vector<quint32> prev = _symbols[i-1].getPos();
////            std::vector<quint32> next = _symbols[i].getPos();
////            generateNewPosition(prev,next,newPos);
////            _symbols.insert(_symbols.begin()+i,s);
//
//            DataPacket packet(10, -1, DataPacket::textTyping);
//            packet.getPayload() = std::make_shared<Message>(Message(Message::insertion,10,s));
////            Message m{insertion,_siteId,s};
//            std::mutex m = _sockets.
//           sendMessage(packet,socket,_sockets->(socket));
////            sendPacket(packet);
//        }

        return 5;
    } else {
        ptr->setType( LoginInfo::login_error);
        ptr->setSiteId(-1);
        ptr->setUser("");
        ptr->setPassword("");
        return -1;
    }


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
    std::cout<<"Client disconnected!"<<std::endl;
    exit(0);
}

LoginInfo ServerThread::loadLoginJson(std::string dir){
    std::ifstream file_input(dir);
    Json::Reader reader;
    Json::Value root;
    reader.parse(file_input, root);

    QString user = QString::fromStdString(root["user"].asString());
    QString password = QString::fromStdString(root["password"].asString());
    LoginInfo data(-1, -1, std::move(user), std::move(password));

    return data;
}

void ServerThread::saveFileJson(std::string dir,std::vector<Symbol> _symbols){//vector<symbol> to json
    std::ofstream file_id;
    file_id.open(dir);
    Json::Value event;
    int index=0;
    for(auto itr=_symbols.begin(); itr != _symbols.end(); ++itr) {
        event[index]["index"] = index;
        event[index]["char"] = QString((*itr).getValue()).toStdString();
        event[index]["symId"]["siteId"] = (*itr).getSymId().getSiteId();
        event[index]["symId"]["count"] = (*itr).getSymId().getCount();

        Json::Value vec(Json::arrayValue);

        for(int i=0; i<(*itr).getPos().size();i++){
            vec.append(Json::Value((*itr).getPos()[i]));
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