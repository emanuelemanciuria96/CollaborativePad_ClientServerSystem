//
// Created by Emanuele on 23/08/2019.
//

#include "SharedEditor.h"
#include "Packet/LoginInfo.h"
#include <vector>
#include <algorithm>
#include <thread>

SharedEditor::SharedEditor(QObject *parent):QObject(parent) {

    this->socket=new QTcpSocket(this);
    _siteId=-1;
    this->connectToServer();
    _counter = 0;
    this->isLogged = false;

    //creo due delimitatori, servono a gestire l'inserimento
    //in coda, in testa o in mezzo al testo allo stesso
    //e identico modo! quando faccio il localInsert, pero',
    //devo ricordare di avere 2 valori in piu'
    std::vector<quint32> v = {0};
    Symbol s('0',-1,-1, v);
    _symbols.push_back(s);
    v = {UINT32_MAX};
    s = Symbol('0',-1,-1, v);
    _symbols.push_back(s);
}

void generateNewPosition( std::vector<quint32>& prev, std::vector<quint32>& next, std::vector<quint32>& newPos, qint32 depth = 0 ){

    quint32 pos;
    if ( depth >= prev.size() ){
        prev.push_back(0);
    }
    if( depth >= next.size() ){
        next.push_back(UINT32_MAX);
    }
    if( next[depth] - prev[depth] > 1 ){
        pos = prev[depth]/2 + next[depth]/2 + ( prev[depth]%2 + next[depth]%2 )/2;
        // in questo modo se i due numeri sono entrambi dispari, la media viene calcolata correttamente
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
    std::vector<quint32> newPos;
    std::vector<quint32> prev = _symbols[index-1].getPos();
    std::vector<quint32> next = _symbols[index].getPos();
    generateNewPosition(prev,next,newPos);
    Symbol s(value,_siteId,_counter++,newPos);
    _symbols.insert(_symbols.begin()+index,s);

    DataPacket packet(_siteId, -1, DataPacket::textTyping);
    packet.setPayload(std::make_shared<Message>(Message::insertion,_siteId,s));

    sendPacket(packet);
//    this->to_string();

}

void SharedEditor::localErase(qint32 index) {

    if ( index > _symbols.size() - 2 ){
        throw "fuori dai limiti"; //da implementare classe eccezione
    }
    index++;
    Symbol s = _symbols[index];
    _symbols.erase(_symbols.begin()+index);

    DataPacket packet(_siteId, -1, DataPacket::textTyping);
    packet.setPayload( std::make_shared<Message>(Message::removal,_siteId,s) );

    sendPacket(packet);
    this->to_string();
}

void SharedEditor::process(const Message &m) {
    std::cout << "Messaggio ricevuto " << m.getAction() << std::endl;
    if ( Message::insertion == m.getAction() ) {
        qint32 pos = 0;
        for ( auto s: _symbols )
            if( s < m.getSymbol() )
                pos++;
            else break;

        _symbols.insert(_symbols.begin()+pos,m.getSymbol());
        emit symbolsChanged(pos, m.getSymbol().getValue(), "insert");
    }
    else if ( Message::removal == m.getAction() ) {
        qint32 pos = 0;

        for ( auto s: _symbols ){
            if( s==m.getSymbol() )
                break;
            pos++;
        }

        if( pos != _symbols.size()) {
            _symbols.erase(_symbols.begin() + pos);
            emit symbolsChanged(pos, m.getSymbol().getValue(), "remove");
        }
    }

}

QString SharedEditor::to_string() {
    QString str;

    std::for_each(_symbols.begin()+1,_symbols.end()-1,
                  [&str](Symbol s){
                      str += s.getValue();
                  });
//    std::cout<<"Local editor: "<<str.toStdString()<<std::endl;
    return str;
}

qint32 SharedEditor::connectToServer() {
    this->socket->connectToHost(QHostAddress::LocalHost, 1234);
    if(this->socket->waitForConnected(1000)) {
        QAbstractSocket::connect(this->socket, &QIODevice::readyRead, this, &SharedEditor::recvPacket);  //ogni volta che arriva un dato sul socket la recvMessage() viene invocata
        std::cout << "Connected!" << std::endl;
        return 1;
    }
    else{
        std::cout << "Not connected: " << socket->errorString().toStdString() << std::endl;
    }

    return -1;
}

void SharedEditor::recvPacket() {
    QDataStream in;
    qint32 source;
    quint32 errcode;
    quint32 type_of_data;

    qDebug() << "Receving packet";

    in.setDevice(this->socket);
    in.setVersion(QDataStream::Qt_5_5);

    in >> source >> errcode >> type_of_data;
    DataPacket packet(source, errcode, (DataPacket::data_t)type_of_data);

    switch (type_of_data) {
        case (DataPacket::login): {
            recvLoginInfo(in);
            break;
        }

        case (DataPacket::textTyping): {
            recvMessage(in);
            break;
        }

        default: {
            std::cout << "Coglione c'è un errore" << std::endl;
            break;
        }
    }
}

void SharedEditor::recvMessage(QDataStream& in) {

    qint32 siteIdM;
    qint32 action;
    QChar ch;
    qint32 siteIdS;
    qint32  count;
    qint32 num;
    qint32 p;
    std::vector<quint32> pos;

    in.setDevice(this->socket);
    in.setVersion(QDataStream::Qt_5_5);

    in >> siteIdM >> action >> ch >> siteIdS >> count >> num;      //riceve sul socket un oggetto Message serializzato
    for(int i=0; i<num; i++){                                      //che viene passato alla process()
        in >> p;
        pos.push_back(p);
    }

    Symbol s(ch, siteIdS, count, pos);
    Message msg(action == 0 ? Message::insertion : Message::removal, siteIdM, s);
    this->process(msg);
//    this->to_string();

    if(this->socket->bytesAvailable()>0)         //se arrivano dati troppo velocemente la recvMessage() non fa in tempo
        emit socket->readyRead();                //a processare i segnali readyRead() e i dati rimangono accodati
}                                                //sul socket, in questo modo svuoto la coda richiamando la recvMessage()

void SharedEditor::sendPacket(DataPacket& packet){
    switch(packet.getTypeOfData()){
        case (DataPacket::login): {
            sendLoginInfo(packet);
            break;
        }

        case (DataPacket::textTyping): {
            sendMessage(packet);
            break;
        }

        default: {
            std::cout<<"Coglione c'è un errore"<<std::endl;
        }
    }
}

void SharedEditor::sendMessage(DataPacket& packet) {
    auto ptr = std::dynamic_pointer_cast<Message>(packet.getPayload());
    QDataStream out;
    qint32 num=ptr->getSymbol().getPos().size();
    out.setDevice(socket);
    out.setVersion(QDataStream::Qt_5_5);

    out << packet.getSource() << packet.getErrcode() << packet.getTypeOfData();
    out << ptr->getSiteId() << (qint32)ptr->getAction() << ptr->getSymbol().getValue() << ptr->getSymbol().getSymId().getSiteId() << ptr->getSymbol().getSymId().getCount() << num;
    for(auto i : ptr->getSymbol().getPos())
        out << (qint32) i;
    socket->waitForBytesWritten(-1);
}

void SharedEditor::sendLoginInfo(DataPacket& packet){
    QDataStream out;
    auto ptr = std::dynamic_pointer_cast<LoginInfo>(packet.getPayload());
    out.setDevice(socket);
    out.setVersion(QDataStream::Qt_5_5);

    out << packet.getSource() << packet.getErrcode() << packet.getTypeOfData();
    out << ptr->getSiteId() << ptr->getType() << ptr->getUser() << ptr->getPassword();
    socket->waitForBytesWritten(-1);
}

void SharedEditor::recvLoginInfo(QDataStream& in){
    quint32 siteId;
    qint32 type;
    QString user;
    QString password;

    in >> siteId >> type >> user >> password;

    if(type == LoginInfo::login_ok) {
        _siteId = siteId;
        std::cout << "client successfully logged!" << std::endl;
        isLogged = true;
    } else {
        std::cout << "client not logged!" << std::endl;
    }
}

void SharedEditor::loginSlot(QString& username, QString& password) {
    std::cout << "sending user=" << username.toStdString() << " and password=" << password.toStdString() << std::endl;
    DataPacket packet(-1, -1, DataPacket::login);
    packet.setPayload( std::make_shared<LoginInfo>( -1, LoginInfo::login_request, std::move(username), std::move(password)) );
    sendPacket(packet);
}

