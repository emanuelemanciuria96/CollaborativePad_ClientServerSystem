//
// Created by muska on 15/10/2019.
//
#include "NetworkServer.h"
#include <QApplication>


NetworkServer::NetworkServer(QObject *parent) : QTcpServer(parent)
{
    //connect(this, SIGNAL(startTest()), this, SLOT(testServer()));

   /* _siteId = 1;
    _counter = 0;
    //creo due delimitatori, servono a gestire l'inserimento
    //in coda, in testa o in mezzo al testo allo stesso
    //e identico modo! quando faccio il localInsert, pero',
    //devo ricordare di avere 2 valori in piu'
    Symbol s('0',-1,-1);
    _symbols->push_back(s);
    _symbols->push_back(s);
    std::vector<qint32> v = {0};
    (*_symbols)[0].setPos(v);
    v = {INT_MAX};
    (*_symbols)[1].setPos(v);
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
    std::cout<<std::this_thread::get_id()<<std::endl;
    qDebug()<< "Creating Thread";

    ServerThread *thread = new ServerThread(socketDesc,&sym_mutex,&_symbols,&skt_mutex,&_sockets,this);
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

/*void NetworkServer::localInsert(qint32 index, QChar value) {

    if ( index > _symbols->size() - 2 ){
        throw "fuori dai limiti"; //da implementare classe eccezione
    }

    index++;
    Symbol s(value,_siteId,_counter++);
    std::vector<qint32> prev = (*_symbols)[index-1].getPos();
    std::vector<qint32> next = (*_symbols)[index].getPos();
    std::vector<qint32> newPos;
    generateNewPosition(prev,next,newPos);
    s.setPos(newPos);
    _symbols->insert(_symbols->begin()+index,s);

    Message m{insertion,_siteId,s};
    sendMessage(m);
    this->to_string();
}*/

/*void NetworkServer::localErase(qint32 index) {

    if ( index > _symbols->size() - 2 ){
        throw "fuori dai limiti"; //da implementare classe eccezione
    }
    index++;
    Symbol s = (*_symbols)[index];
    _symbols->erase(_symbols->begin()+index);

    Message m{removal,_siteId,s};
    sendMessage(m);
    this->to_string();
}*/

void NetworkServer::process(const Message &m) {

    if ( insertion == m.getAction() ) {
        qint32 pos = 0;
        for ( auto s: _symbols )
            if( s.getPos() < m.getSymbol().getPos() )
                pos++;
            else break;

        _symbols.insert(_symbols.begin()+pos,m.getSymbol());
    }
    else if ( removal == m.getAction() ) {
        qint32 pos = -1;
        for ( auto s: _symbols ){
            pos++;
            if( s.getPos()==m.getSymbol().getPos() && s == m.getSymbol() )
                break;
        }

        if( pos != -1)
            _symbols.erase(_symbols.begin()+pos);
    }
}

void NetworkServer::to_string() {
    QString str;

    std::for_each(_symbols.begin(),_symbols.end(),
                  [&str](Symbol s){
                      str += s.getValue();
                  });
    std::cout<<"Local editor: "<<str.toStdString()<<std::endl;
}


void NetworkServer::recvMessage() {
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

    in >> siteIdM >> action >> ch >> siteIdS >> count >> num;
    for(int i=0; i<num; i++){
        in >> p;
        pos.push_back(p);
    }

    Symbol s(ch, siteIdS, count,pos);
    s.setPos(pos);
    Message msg(action == 0 ? insertion : removal, siteIdM, s);
    this->process(msg);
    this->to_string();
    if(this->socket->bytesAvailable()>0)
        emit socket->readyRead();
    if(this->_symbols.size()==4) {
        std::cout << "Test" << std::endl;           //controlla che siano arrivati 'c' e 'a' e fa partire la simulazione del secondo client
        emit startTest();
    }

}

void NetworkServer::sendMessage(Message& msg) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    qint32 num=msg.getSymbol().getPos().size();
    out.setVersion(QDataStream::Qt_5_5);

    out << msg.getSiteId() << (qint32) (msg.getAction() == insertion ? 0 : 1) << msg.getSymbol().getValue() << msg.getSymbol().getSymId().getSiteId() << msg.getSymbol().getSymId().getCount() << num;
    for(auto i : msg.getSymbol().getPos())
        out << (qint32) i;
    this->socket->write(block);
    this->socket->waitForBytesWritten(3000);
}

void NetworkServer::deleteSocket() {
    this->socket->deleteLater();
    this->_symbols.erase(this->_symbols.begin(), this->_symbols.end());
    std::cout << "Client Disconnected!" << std::endl;
}



/*void NetworkServer::testServer() {
    this->localInsert(2, 't');
    this->localInsert(1, 'h');
    this->localErase(0);
}*/

