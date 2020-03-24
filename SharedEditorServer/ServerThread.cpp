//
// Created by utente on 03/11/2019.
//

#include <iostream>
#include <utility>
#include <QtCore/QDataStream>
#include "ServerThread.h"
#include "NetworkServer.h"

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
ServerThread::ServerThread(qintptr socketDescriptor, MessageHandler *msgHandler,std::shared_mutex *skt_mutex,
                            std::vector<QTcpSocket*> *sockets,QObject *parent):QThread(parent){
    this->skt_mutex = skt_mutex;
    this->_sockets = sockets;
    this->socketDescriptor = socketDescriptor;
    this->msgHandler = msgHandler;
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
        std::unique_lock ul(*skt_mutex);
        _sockets->push_back(socket);
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

    QAbstractSocket::connect(this->socket, &QIODevice::readyRead, this, &ServerThread::recvMessage);
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

    Symbol sym(ch,siteIdS,count,pos);
    Message msg((action_t)action,siteIdM,sym);
    if( action == insertion ){
        msgHandler->submit(NetworkServer::localInsert,msg);
    }
    else{
        msgHandler->submit(NetworkServer::localErase,msg);
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
    {
        std::shared_lock sl(*skt_mutex);
        for (auto skt: *_sockets) {
            if (skt != socket) {
                sendMessage(msg, skt);
            }
        }
    }

    ((NetworkServer*)this->parent())->to_string();
}

void ServerThread::sendMessage(Message& msg, QTcpSocket *skt) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    qint32 num=msg.getSymbol().getPos().size();
    out.setVersion(QDataStream::Qt_5_5);

    out << msg.getSiteId() << (qint32)msg.getAction() << msg.getSymbol().getValue() << msg.getSymbol().getSymId().getSiteId() << msg.getSymbol().getSymId().getCount() << num;
    for(auto i : msg.getSymbol().getPos())
        out << (qint32) i;
    skt->write(block);
    skt->waitForBytesWritten(-1);
}

void ServerThread::disconnected()
{
    socket->deleteLater();
    std::cout<<"Client disconnected!"<<std::endl;
    exit(0);
}
