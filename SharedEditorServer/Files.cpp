//
// Created by utente on 01/08/2020.
//

#include <set>
#include <iostream>
#include "Files.h"

enum{file,counter,mutex,dirty_bit};


std::shared_ptr<const std::vector<Symbol>> Files::openFile(QString& fileName) {

    std::vector<Symbol> symbles;
    std::shared_ptr<const std::vector<Symbol>> copy_syms;

    std::unique_lock ul(files_mtx);
    auto i = opened_files.find(fileName);
    if ( i!=opened_files.end() ){
        std::unique_lock ul_sym(*std::get<mutex>(i->second));
        std::get<counter>(i->second)++;
        copy_syms = std::shared_ptr<const std::vector<Symbol>>(new std::vector<Symbol>(std::get<file>(i->second)) );
    }
    else{
        loadFileJson(fileName.toStdString(),symbles);
        copy_syms = std::shared_ptr<const std::vector<Symbol>>(new std::vector<Symbol>(symbles) );
        opened_files.insert( std::make_pair( fileName,std::make_tuple(symbles,1,new std::shared_mutex(),false) ) );
    }
    ul.unlock();

    return copy_syms;
}

void Files::closeFile(QString &fileName) {

    std::shared_mutex *tmp = nullptr;

    std::unique_lock ul(files_mtx);
    auto i = opened_files.find(fileName);
    if ( i!=opened_files.end() ){
        std::unique_lock ul_sym(*std::get<mutex>(i->second));
        if (--std::get<counter>(i->second) == 0) {
            tmp = std::get<mutex>(i->second);
            if (std::get<dirty_bit>(i->second))
                saveFileJson(fileName.toStdString(), std::get<file>(i->second));
            opened_files.erase(i);
        }
    }

    delete tmp;

}

void Files::addSymbolInFile(QString& fileName, Symbol& sym){

    std::shared_lock sl(files_mtx);
    auto i = opened_files.find(fileName);

    std::unique_lock ul_sym(*std::get<mutex>(i->second));
    auto pos = std::lower_bound(std::get<file>(i->second).begin(), std::get<file>(i->second).end(), sym);
    std::get<file>(i->second).insert(pos, sym);
    std::get<dirty_bit>(i->second) = true;

}

void Files::rmvSymbolInFile(QString& fileName, Symbol& sym){

    std::shared_lock sl(files_mtx);
    auto i = opened_files.find(fileName);

    std::unique_lock ul_sym(*std::get<mutex>(i->second));
    auto pos = std::lower_bound(std::get<file>(i->second).begin(), std::get<file>(i->second).end(), sym);
    if (*pos == sym ) {
        std::get<file>(i->second).erase(pos);
        std::get<dirty_bit>(i->second) = true;
    }

}

void Files::saveChanges(QString &fileName) {

    std::shared_lock sl(files_mtx);
    auto i = opened_files.find(fileName);
    std::shared_lock sl_sym(*std::get<mutex>(i->second));
    if( !std::get<dirty_bit>(i->second) )
        return;
    saveFileJson(fileName.toStdString(), std::get<file>(i->second));

}

void Files::saveAll() {

    std::shared_lock sl(files_mtx);
    for( auto of: opened_files ) {
        std::shared_lock sl_sym(*std::get<mutex>(of.second));
        std::cout<<" ---- actual number of inserted symbles: "<<std::get<file>(of.second).size()<<std::endl;
        if (!std::get<dirty_bit>(of.second))
            continue;
        saveFileJson(of.first.toStdString(), std::get<file>(of.second));
    }
}

/*
void Files::QTsaveFileJson(const std::string& dir,std::vector<Symbol> _symbols){
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

void Files::saveFileJson(std::string dir,std::vector<Symbol>& _symbols){//vector<symbol> to json
    std::ofstream file_id;
    file_id.open(dir);
    Json::Value event;
    int index=0;
    for(auto itr:_symbols) {
        event[index]["index"] = index;
        event[index]["char"] = (uint)itr.getValue().unicode();
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


void Files::loadFileJson(std::string dir, std::vector<Symbol> &symbles){//json to vector<symbol>
    std::ifstream file_input(dir);
    Json::Reader reader;
    Json::Value root;
    reader.parse(file_input, root);

    for(int i=0; i<root.size(); i++) {
        QChar value((short)root[i]["char"].asUInt());
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

}

Files::~Files() {
    // anche se successivamente a questo salvataggio ne dovesse essere chiamato qualcun altro
    // non cambierebbe nulla, anzi, sarebbe ben accetto. L'importante è che, al momento della
    // distruzione, ci sia un punto di salvataggio
    saveAll();
    std::unique_lock ul(files_mtx);
    for( auto item: opened_files ){
        delete std::get<mutex>(item.second);
    }
    opened_files.clear();
}
