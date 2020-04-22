//
// Created by Emanuele on 23/08/2019.
//

#include "SharedEditor.h"
#include "Packet/LoginInfo.h"
#include <vector>
#include <algorithm>

SharedEditor::SharedEditor(QObject *parent):QObject(parent) {

    _siteId=-1;
    _counter = 0;
    this->isLogged = false;

    transceiver = new Transceiver;
    transceiver->moveToThread(transceiver);

    connect(transceiver,SIGNAL(finished()),this,SLOT(deleteThread()));
    connect(transceiver,&Transceiver::readyToProcess,this,&SharedEditor::process,Qt::QueuedConnection);


    transceiver->start();

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

quint32 intermediateValue(quint32 prev,quint32 next,double factor){
    // calcolo del valore intermedio
    double tmp=(next-prev)*factor;
    quint32 val=prev+tmp;
    if(val==next){
        val--;
    } else if (val==prev){
        val++;
    }
    return val;
}
void generateNewPosition2(std::vector<quint32>& prev, std::vector<quint32>& next, std::vector<quint32>& newPos){
    quint32 max=UINT_MAX;
    double factor=0.05;
    //double factor=0.015625; // 1/64
    int sizePrev=prev.size();
    int sizeNext=next.size();
    int min=std::min(sizePrev,sizeNext);
    for (int i = 0; i<min; i++) { // cerco il primo valore intermedio, se lo trovo esco
        if(next[i]-prev[i]>1){
            newPos.push_back(intermediateValue(prev[i],next[i],factor));
            return;
        }else{
            newPos.push_back(prev[i]);
        }
    }
    if(sizePrev>sizeNext) { // distinguo due casi
        for (int i = min; i < sizePrev; i++) {
            if (max - prev[i] > 1) {
                newPos.push_back(intermediateValue(prev[i], max, factor));
                return;
            } else {
                newPos.push_back(prev[i]);
            }
        }
    } else {
        for (int i = min; i < sizeNext; i++) {
            if (next[i] > 1) {
                newPos.push_back(intermediateValue(0, next[i], factor));
                return;
            } else {
                newPos.push_back(0);
            }
        }
    }
    newPos.push_back(intermediateValue(0, max, factor));
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
        if( (next[depth] - prev[depth])>256 )
            pos = prev[depth] + ((next[depth] - prev[depth])>>6);
        else
            pos = (prev[depth]>>1) + (next[depth]>>1) + (( (prev[depth]&1) + (next[depth]&1) )>>1);
            // la formula di sopra calcola il punto medio tenendo conto del resto (calcolato con un AND ed uno SHIFT)
    }
    else if ( next[depth] - prev[depth] <= 1 ){
        pos = prev[depth];
        generateNewPosition(prev, next, newPos, depth+1);
    }
    newPos.insert(newPos.begin(),pos);
}

void SharedEditor::loginSlot(QString& username, QString& password) {
    std::cout << "sending user=" << username.toStdString() << " and password=" << password.toStdString() << std::endl;
    DataPacket packet(-1, -1, DataPacket::login);
    packet.setPayload( std::make_shared<LoginInfo>( -1, LoginInfo::login_request, std::move(username), std::move(password)) );

    int id = qMetaTypeId<DataPacket>();
    emit transceiver->getSocket()->sendPacket(packet);
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

    int id = qMetaTypeId<DataPacket>();
    emit transceiver->getSocket()->sendPacket(packet);
//    this->to_string();
    emit test1();

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

    int id = qMetaTypeId<DataPacket>();
    emit transceiver->getSocket()->sendPacket(packet);
    this->to_string();

    emit test1();
}

void SharedEditor::process(DataPacket pkt) {

    switch (pkt.getTypeOfData()){
        case DataPacket::login :
            processLoginInfo(*std::dynamic_pointer_cast<LoginInfo>(pkt.getPayload()));
            break;
        case DataPacket::textTyping :
            processMessages(*std::dynamic_pointer_cast<StringMessages>(pkt.getPayload()));
            break;
        default:
            std::cout<<"Coglione 2 volte, c'è un errore"<<std::endl;
            throw std::exception();
    }

    auto m = std::dynamic_pointer_cast<Message>(pkt.getPayload());
    emit test1();

}

void SharedEditor::processLoginInfo(LoginInfo &logInf) {
    if(logInf.getType() == LoginInfo::login_ok) {
        _siteId = logInf.getSiteId();
        std::cout << "client successfully logged!" << std::endl;
        isLogged = true;
    } else {
        std::cout << "client not logged!" << std::endl;
    }
}

void SharedEditor::processMessage(Message &m) {

    qint32 pos = 0;
    if ( Message::insertion == m.getAction() ) {

        auto i = std::lower_bound(_symbols.begin(),_symbols.end(),m.getSymbol());
        pos = i - _symbols.begin();
        _symbols.insert(i,m.getSymbol());

        emit symbolsChanged(pos, m.getSymbol().getValue(), "insert");
    }
    else if ( Message::removal == m.getAction() ) {

        auto i = std::lower_bound(_symbols.begin(),_symbols.end(),m.getSymbol());
        pos = i - _symbols.begin();

        if( *i == m.getSymbol() ) {
            _symbols.erase(i);
            emit symbolsChanged(pos, m.getSymbol().getValue(), "remove");
        }
        else
            throw std::exception(); //errore fatale
    }
}

void SharedEditor::processMessages(StringMessages &strMess) {
    for( auto m : strMess.stringToMessages() )
        processMessage(m);
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

void SharedEditor::test() {
   /* for(auto s:_symbols) {
        std::cout << s.getValue().toLatin1() << " - " << s.getPos().size() << " - ";
        for(auto p: s.getPos())
            std::cout<<p<<"; ";
        std::cout<<std::endl;
    }*/

    std::cout<<"#caratteri inseriti: "<<_symbols.size()-2<<std::endl;

}

void SharedEditor::deleteThread() {
    transceiver->deleteLater();
    exit(-1);
}



