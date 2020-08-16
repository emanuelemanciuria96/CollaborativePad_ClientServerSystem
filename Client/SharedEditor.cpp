//
// Created by Emanuele on 23/08/2019.
//

#include "SharedEditor.h"
#include "Packet/LoginInfo.h"
#include <vector>
#include <algorithm>
#include <tuple>
#include <string>

SharedEditor::SharedEditor(QObject *parent):QObject(parent) {

    _siteId=-1;
    _counter = 0;
    this->isLogged = false;

    transceiver = new Transceiver(_siteId);
    transceiver->moveToThread(transceiver);

    connect(transceiver,SIGNAL(finished()),this,SLOT(deleteThread()));
    connect(transceiver,&Transceiver::readyToProcess,this,&SharedEditor::process,Qt::QueuedConnection);
    connect(transceiver,&Transceiver::deleteText,this,&SharedEditor::deleteText,Qt::QueuedConnection);


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
    quint32 max=UINT32_MAX;
    double factor=0.001;
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
        if( (next[depth] - prev[depth])>512 )
            pos = prev[depth] + ((next[depth] - prev[depth])>>7);
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
    packet.setPayload(std::make_shared<Message>(Message::insertion,_siteId,s,index));

    int id = qMetaTypeId<DataPacket>();
    emit transceiver->getSocket()->sendPacket(packet);
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
    packet.setPayload( std::make_shared<Message>(Message::removal,_siteId,s,index) );

    int id = qMetaTypeId<DataPacket>();
    emit transceiver->getSocket()->sendPacket(packet);
    this->to_string();


}

void SharedEditor::sendCursorPos(qint32 pos) {
    DataPacket packet(_siteId, -1, DataPacket::cursorPos);
    packet.setPayload(std::make_shared<CursorPosition>(pos, _siteId));

    emit transceiver->getSocket()->sendPacket(packet);
}

void SharedEditor::process(DataPacket pkt) {

    switch (pkt.getTypeOfData()){
        case DataPacket::login :
            processLoginInfo(*std::dynamic_pointer_cast<LoginInfo>(pkt.getPayload()));
            break;
        case DataPacket::textTyping :
            processMessages(*std::dynamic_pointer_cast<StringMessages>(pkt.getPayload()));
            break;
        case DataPacket::command :
            processCommand(*std::dynamic_pointer_cast<Command>(pkt.getPayload()));
            break;
        case DataPacket::cursorPos:
            processCursorPos(*std::dynamic_pointer_cast<CursorPosition>(pkt.getPayload()));
            break;
        default:
            std::cout<<"Coglione 2 volte, c'è un errore"<<std::endl;
            throw std::exception();
    }

    auto m = std::dynamic_pointer_cast<Message>(pkt.getPayload());


}

void SharedEditor::processCursorPos(CursorPosition &curPos) {
    emit RemoteCursorPosChanged(curPos.getPos(), curPos.getSiteId());
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

qint32 SharedEditor::getIndex(Message &m) {
    qint32 pos=m.getLocalIndex();//search index
    if(pos>_symbols.size()-1){
        pos=_symbols.size()-1;
    }
    if(m.getSymbol()>_symbols[pos]){
        for(qint32 i=pos+1;i<_symbols.size();i++){
            if(m.getSymbol() < _symbols[i] || m.getSymbol() == _symbols[i]){
                return i;
            }
        }
    }else{
        for(qint32 i=pos-1;i>=0;i--){
            if(m.getSymbol()>_symbols[i]){
                return i+1;
            }
        }
    }
    return pos;
}


void SharedEditor::processMessages(StringMessages &strMess) {

    std::vector<std::tuple<qint32,bool, QChar,qint32>> vt;

    for( auto m: strMess.stringToMessages() ) {
        qint32 pos=getIndex(m);
        if(m.getAction()==Message::insertion){
            _symbols.insert(_symbols.begin()+pos,m.getSymbol());
            vt.push_back(std::tuple<qint32 ,bool,QChar,qint32>(pos,1,m.getSymbol().getValue(),m.getSiteId()));
        }else if(_symbols[pos]==m.getSymbol()){
            vt.push_back(std::tuple<qint32, bool, QChar,qint32>(pos, 0, m.getSymbol().getValue(),m.getSiteId()));
            _symbols.erase(_symbols.begin()+pos);
        }
    }
    //Refresh GUI

    if(vt.size()<1){
        return;
    }

    QString s="";
    qint32 firstPos=std::get<0>(vt[0]);
    vt.push_back(std::tuple<qint32 ,bool,QChar,qint32>(-8,1,2,9));
    for(int i=0;i<vt.size()-1;i++) {
        s += std::get<2>(vt[i]);

        // std::cerr << "stringa: " << s.toStdString() << std::endl;

        if(std::get<1>(vt[i])==1) {
            if (std::get<1>(vt[i+1])==1 and std::get<0>(vt[i+1]) == std::get<0>(vt[i]) + 1) {
            } else {
                //qDebug()<<"insert "<<s<<" in pos "<<firstPos;
                emit symbolsChanged(firstPos, s, std::get<3>(vt[i]),Message::insertion);
                s = "";
                firstPos = std::get<0>(vt[i+1]);
            }
        }else {
            if (std::get<1>(vt[i+1])==0 and std::get<0>(vt[i]) == std::get<0>(vt[i+1])) {
            } else {
                //qDebug()<<"remove "<<s<<" in pos "<<firstPos+s.size()-1;
                emit symbolsChanged(firstPos, s, std::get<3>(vt[i]), Message::removal);
                s = "";
                firstPos = std::get<0>(vt[i+1]);
            }
        }
    }

}

void SharedEditor::deleteText(){
    emit deleteAllText();
}

void SharedEditor::processCommand(Command& cmd){
    switch (cmd.getCmd()) {
        case (Command::cd): {
           processCdCommand(cmd);
           break;
        }

        case (Command::rm): {
            break;
        }

        case (Command::cp): {
            break;
        }

        case (Command::mv): {
            break;
        }

        case (Command::opn): {
            break;
        }

        case (Command::cls): {
            break;
        }

        default:
            std::cout << "Coglione errore nel Command" << std::endl;
    }
}

void SharedEditor::processCdCommand(Command& cmd){
    std::cout << "cd args:" << std::endl;
    for (auto &a: cmd.getArgs())
        std::cout << a.toStdString() << std::endl;
}

void SharedEditor::testCommand(){ //funzione per testare la command, fa cagare ma per ora non ho idee migliori
   /* DataPacket packet(-1, -1, DataPacket::command);
    packet.setPayload( std::make_shared<Command>( _siteId, Command::cd, QVector<QString>(1, "")));
    emit transceiver->getSocket()->sendPacket(packet); //questo serve a farsi inviare il contenuto della root*/

    /*DataPacket packet(-1, -1, DataPacket::command);
    packet.setPayload( std::make_shared<Command>( _siteId, Command::mkdir, QVector<QString>(1, "/Cartella test")));
    emit transceiver->getSocket()->sendPacket(packet); //questo serve a creare una cartella "Cartella test" nella root*/

    /*DataPacket packet(-1, -1, DataPacket::command);
    packet.setPayload( std::make_shared<Command>( _siteId, Command::rm, QVector<QString>(1, "/Cartella1>D")));
    emit transceiver->getSocket()->sendPacket(packet); //questo serve a cancellare la cartella "Cartella1"*/

    /*DataPacket packet(-1, -1, DataPacket::command);
    packet.setPayload( std::make_shared<Command>( _siteId, Command::opn, QVector<QString>(1, "/prova>F")));
    emit transceiver->getSocket()->sendPacket(packet); //questo serve ad aprire il file "prova.json" sul server*/

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


void SharedEditor::deleteThread() {
    transceiver->deleteLater();
    exit(-1);
}

qint32 SharedEditor::getSiteId() {
    return _siteId;
}




