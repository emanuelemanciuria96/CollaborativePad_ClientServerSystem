//
// Created by Emanuele on 23/08/2019.
//

#include "SharedEditor.h"
#include <vector>
#include <algorithm>
#include <thread>

SharedEditor::SharedEditor(QObject *parent):QObject(parent) {

    this->socket=new QTcpSocket(this);
    _siteId=-1;                             //inizialmente -1 per fare in modo che alla ricezione
    _siteId = this->connectToServer();      //del vero siteId da parte del server la recvMessage() ritorni subito
    _counter = 0;

    //creo due delimitatori, servono a gestire l'inserimento
    //in coda, in testa o in mezzo al testo allo stesso
    //e identico modo! quando faccio il localInsert, pero',
    //devo ricordare di avere 2 valori in piu'
    Symbol s('0',-1,-1);
    _symbols.push_back(s);
    _symbols.push_back(s);
    std::vector<qint32> v = {0};
    _symbols[0].setPos(v);
    v = {INT_MAX};
    _symbols[1].setPos(v);
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

void SharedEditor::localInsert(qint32 index, QChar value) {

    if ( index > _symbols.size() - 2 ){
        throw "fuori dai limiti"; //da implementare classe eccezione
    }

    index++;
    Symbol s(value,_siteId,_counter++);
    std::vector<qint32> prev = _symbols[index-1].getPos();
    std::vector<qint32> next = _symbols[index].getPos();
    std::vector<qint32> newPos;
    generateNewPosition(prev,next,newPos);
    s.setPos(newPos);
    _symbols.insert(_symbols.begin()+index,s);

    Message m{insertion,_siteId,s};
    sendMessage(m);
    this->to_string();
}

void SharedEditor::localErase(qint32 index) {

    if ( index > _symbols.size() - 2 ){
        throw "fuori dai limiti"; //da implementare classe eccezione
    }
    index++;
    Symbol s = _symbols[index];
    _symbols.erase(_symbols.begin()+index);

    Message m{removal,_siteId,s};
    sendMessage(m);
    this->to_string();
}

void SharedEditor::process(const Message &m) {

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

void SharedEditor::to_string() {
    QString str;

    std::for_each(_symbols.begin()+1,_symbols.end()-1,
                  [&str](Symbol s){
                      str += s.getValue();
                  });
    std::cout<<"Local editor: "<<str.toStdString()<<std::endl;
}

qint32 SharedEditor::connectToServer() {
    this->socket->connectToHost(QHostAddress::LocalHost, 1234);
    if(this->socket->waitForConnected(1000)) {
        if(socket->waitForReadyRead(1000)) {          //non ho ancora collegato il segnale readyRead a recvMessage, quindi
            QDataStream in;                                 //leggo sul socket in modo bloccante (per 3000 ms)
            in.setDevice(this->socket);
            in.setVersion(QDataStream::Qt_5_5);
            qint32 type;
            in>>type;
            in >> _siteId;                                  //ricevo il SiteId
            std::cout<<"SiteId: "<<_siteId<<std::endl;
            QAbstractSocket::connect(this->socket, &QIODevice::readyRead, this, &SharedEditor::recvMessage);  //ogni volta che arriva un dato sul socket la recvMessage() viene invocata
        }
        else{
            std::cout << "Not connected: " << socket->errorString().toStdString() << std::endl;
        }
    }
    else{
        std::cout << "Not connected: " << socket->errorString().toStdString() << std::endl;
    }

    return -1;
}

void SharedEditor::recvMessage() {

    QDataStream in;
    qint32 siteIdM;
    qint32 action;
    QChar ch;
    qint32 siteIdS;
    qint32  count;
    qint32 num;
    qint32 p;
    std::vector<qint32> pos;

    in.setDevice(this->socket);
    in.setVersion(QDataStream::Qt_5_5);

    in >> siteIdM >> action >> ch >> siteIdS >> count >> num;      //riceve sul socket un oggetto Message serializzato
    for(int i=0; i<num; i++){                                      //che viene passato alla process()
        in >> p;
        pos.push_back(p);
    }

    Symbol s(ch, siteIdS, count);
    s.setPos(pos);
    Message msg(action == 0 ? insertion : removal, siteIdM, s);
    this->process(msg);
    this->to_string();

    if(this->socket->bytesAvailable()>0)         //se arrivano dati troppo velocemente la recvMessage() non fa in tempo
        emit socket->readyRead();                //a processare i segnali readyRead() e i dati rimangono accodati
}                                                //sul socket, in questo modo svuoto la coda richiamando la recvMessage()

void SharedEditor::sendMessage(Message& msg) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    qint32 num=msg.getSymbol().getPos().size();
    out.setVersion(QDataStream::Qt_5_5);

    out << msg.getSiteId() << (qint32) (msg.getAction() == insertion ? 0 : 1) << msg.getSymbol().getValue() << msg.getSymbol().getSymId().getSiteId() << msg.getSymbol().getSymId().getCount() << num;
    for(auto i : msg.getSymbol().getPos())
        out << (qint32) i;                                      //invia al server un oggetto Message serializzato sul socket
    this->socket->waitForBytesWritten(-1);
}

