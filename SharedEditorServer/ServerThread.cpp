//
// Created by utente on 03/11/2019.
//

#include <iostream>
#include <utility>
#include <QtCore/QDataStream>
#include "ServerThread.h"



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
ServerThread::ServerThread(qintptr socketDescriptor, std::mutex *sym_mutex, std::vector<Symbol> *symbols,
                           std::mutex *skt_mutex, std::vector<QTcpSocket*> *sockets,QObject *parent):QThread(parent){
    this->skt_mutex = skt_mutex;
    this->_sockets = sockets;
    this->sym_mutex = sym_mutex;
    this->_symbols = symbols;
    this->socketDescriptor = socketDescriptor;
}

void ServerThread::run()
{
    socket = new QTcpSocket();

    if ( !socket->setSocketDescriptor(this->socketDescriptor) )   //setto il descriptor del socket
    {
        emit error (socket->error());         //da gestire
        return;
    }

    /**
     * queste 4 righe sono una prova di scambio di siteID, il primo valore ( 1 )
     * serve semplicemente ad indicare al client che si tratta di una comunicazione
     * del siteID
     */
    QDataStream out;
    out.setDevice(socket);
    out.setVersion(QDataStream::Qt_5_5);
    out<<DataPacket::login<<5;

    connect(socket, SIGNAL(readyRead()), this, SLOT(recvMessage()));
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

void ServerThread::recvMessage()
{
    std::cout<<std::this_thread::get_id()<<" reading from socket "<<this->socketDescriptor<<std::endl;

    QDataStream in;
    qint32 siteIdM;
    qint32 action;
    QChar ch;
    qint32 siteIdS;
    qint32  count;
    qint32 num;
    qint32 p;
    std::vector<qint32> pos;

    qDebug()<<"Receving message";

    in.setDevice(this->socket);
    in.setVersion(QDataStream::Qt_5_5);

    in >> siteIdM >> action >> ch >> siteIdS >> count >> num; //il protocollo scelto per il passaggio della posizione richiede
    for(int i=0; i<num; i++){                                 //la lettura di un valore ad indicarne la lunghezza di pos
        in >> p;
        pos.push_back(p);
    }

    Symbol sym(ch,siteIdS,count,pos);
    if( action == insertion ){
        int i = 0;
        std::unique_lock ul(*sym_mutex);
        for (auto s: *_symbols)   //algoritmo lineare, migliorabile
            if (!(s < (*_symbols)[i]))
                i++;

        _symbols->insert(_symbols->begin() + i, sym);
    }
    else{
        int i = 0;
        std::unique_lock ul(*sym_mutex);
        for( auto s: *_symbols) //algoritmo lineare anche qui, migliorabile (penso che nella libreria STL ci possa essere già qualcosa di implementato)
            if( !(s==(*_symbols)[i]) )
                i++;
        _symbols->erase(_symbols->begin()+i);
    }

    Message m((action_t)action,siteIdM,sym);
    std::unique_lock ul(*skt_mutex);
    for( auto skt: *_sockets){
        if ( skt != socket ){
            sendMessage(m,skt);
        }
    }

    ((NetworkServer*)this->parent())->to_string();
}

void ServerThread::sendMessage(Message& msg, QTcpSocket *skt) {
    QDataStream out;
    out.setDevice(socket);
    out.setVersion(QDataStream::Qt_5_5);

    qint32 num=msg.getSymbol().getPos().size();

    out << msg.getSiteId() << (qint32)msg.getAction() << msg.getSymbol().getValue() << msg.getSymbol().getSymId().getSiteId() << msg.getSymbol().getSymId().getCount() << num;
    for(auto i : msg.getSymbol().getPos())
        out << (qint32) i;
    skt->waitForBytesWritten(-1);
}

void ServerThread::disconnected()
{
    socket->deleteLater();
    std::cout<<"Client disconnected!"<<std::endl;
    exit(0);
}
