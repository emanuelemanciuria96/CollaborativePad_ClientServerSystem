//
// Created by utente on 01/08/2020.
//

#include <set>
#include <iostream>
#include "Files.h"

enum{file,counter,dirty_bit};
QVector<QString> Files::fonts{"Arial","Arial Black","Comic Sans MS", "Courier","Georgia","Impact","Tahoma","Times New Roman","Trebuchet MS","Verdana"};

std::shared_ptr<std::vector<Symbol>> Files::openFile(QString& fileName) {

    auto symbles = std::make_shared<std::vector<Symbol>>();

    auto i = opened_files.find(fileName);
    if ( i!=opened_files.end() ){
        std::get<counter>(i->second)++;
        for(auto s: std::get<file>(i->second))
            symbles->push_back(s.first);
    }
    else{
        auto i = opened_files.insert( std::make_pair( fileName,std::make_tuple(std::map<Symbol,int>(),1,false) ) ).first;
        loadFileJson(fileName.toStdString(),std::get<file>(i->second),symbles);
    }

    return symbles;
}

bool Files::closeFile(QString &fileName) {

    auto i = opened_files.find(fileName);
    if ( i!=opened_files.end() ){
        if (--std::get<counter>(i->second) == 0) {
            if (std::get<dirty_bit>(i->second))
                saveFileJson(fileName.toStdString(), std::get<file>(i->second));
            opened_files.erase(i);
        }
    }

    return !opened_files.empty(); // deve ritornare false se è vuoto

}

bool Files::deleteFile(QString &fileName) {

    auto i = opened_files.find(fileName);
    if ( i!=opened_files.end() ){
        opened_files.erase(i);
    }

    QFile file(".\\files\\"+fileName);
    file.remove();
    /*std::string command = "del .\\files\\"+fileName.toStdString();
    system(command.c_str());
*/
    bool tmp =  !opened_files.empty();
    return tmp; // deve ritornare false se è vuoto
}


void Files::addSymbolInFile(QString& fileName, Symbol& sym){

    auto i = opened_files.find(fileName);

    if(i != opened_files.end()) {
        std::get<file>(i->second).insert(std::make_pair(sym,0));
        std::get<dirty_bit>(i->second) = true;
    }
}

void Files::rmvSymbolInFile(QString& fileName, Symbol& sym){

    auto i = opened_files.find(fileName);

    if(i != opened_files.end()) {
        auto pos = std::get<file>(i->second).lower_bound(sym);
        if ( pos->first == sym ) {
            std::get<file>(i->second).erase(pos);
            std::get<dirty_bit>(i->second) = true;
        }
    }
}

void Files::modSymbolInFile(QString &fileName, Symbol &sym) {

    auto i = opened_files.find(fileName);

    if(i != opened_files.end()) {
        auto node = std::get<file>(i->second).extract(sym);
        if ( !node.empty() ) {
            node.key().mergeFormat(sym.getFormat());
            std::get<file>(i->second).insert(std::move(node));
            std::get<dirty_bit>(i->second) = true;
        }
    }
}

void Files::saveChanges(QString &fileName) {

    auto i = opened_files.find(fileName);
    if( !std::get<dirty_bit>(i->second) )
        return;
    saveFileJson(fileName.toStdString(), std::get<file>(i->second));

}

void Files::saveAll() {

    for( auto of: opened_files ) {
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

void Files::saveFileJson(std::string dir,std::map<Symbol,int>& symbles){//vector<symbol> to json
    std::ofstream file_id;
    file_id.open("./files/"+dir);
    Json::Value event;
    int index=0;
    for( auto itr: symbles) {
        event[index]["index"] = index;
        event[index]["font"] = fonts.indexOf(itr.first.getFormat().fontFamily());
        event[index]["size"] = itr.first.getFormat().fontPointSize();
        int col = std::stoi( itr.first.getFormat().foreground().color().name().remove(0,1).toStdString(),0,16 );
        std::cout<<"saving color: "<<col;
        event[index]["color"] = std::stoi( itr.first.getFormat().foreground().color().name().remove(0,1).toStdString(),0,16 );
        event[index]["underline"] = itr.first.getFormat().fontUnderline();
        event[index]["bold"] = itr.first.getFormat().font().bold();
        event[index]["italic"] = itr.first.getFormat().fontItalic();
        event[index]["char"] = (uint)itr.first.getValue().unicode();
        event[index]["symId"]["siteId"] = itr.first.getSymId().getSiteId();
        event[index]["symId"]["count"] = itr.first.getSymId().getCount();

        Json::Value vec(Json::arrayValue);

        for(int i=0; i<itr.first.getPos().size();i++){
            vec.append(Json::Value(itr.first.getPos()[i]));
        }
        event[index]["pos"]=vec;

        index++;
    }

    Json::StyledWriter styledWriter;
    file_id << styledWriter.write(event);

    file_id.close();
}


void Files::loadFileJson(std::string dir,std::map<Symbol,int>& symbles, std::shared_ptr<std::vector<Symbol>> syms){ //json to vector<symbol>

    std::ifstream file_input;
    file_input.open("./files/"+dir);
    Json::Reader reader;
    Json::Value root;
    reader.parse(file_input, root);

    for(int i=0; i<root.size(); i++) {
        QTextCharFormat frmt;
        frmt.setFontFamily(fonts[root[i]["font"].asInt()]);
        frmt.setFontPointSize(root[i]["size"].asFloat());
        std::stringstream str;
        str<<std::hex<<root[i]["color"].asUInt();
        frmt.setForeground(QColor("#"+QString::fromStdString(str.str()) ));
        frmt.setFontUnderline(root[i]["underline"].asBool());
        frmt.setFontWeight(root[i]["bold"].asBool()? QFont::Bold : QFont::Normal);
        frmt.setFontItalic(root[i]["italic"].asBool());

        QChar value((short)root[i]["char"].asUInt());
        qint32 _siteId=root[i]["symId"]["siteId"].asUInt64();
        qint32 _counter=root[i]["symId"]["count"].asUInt64();
        std::vector<quint32> pos;
        for(int j=0;j<root[i]["pos"].size();j++){
            qint32 val=root[i]["pos"][j].asUInt64();
            pos.push_back(val);
        }
        Symbol s(value,_siteId,_counter, pos, frmt);
        syms->push_back(s);
        symbles.insert(symbles.end(),std::make_pair(s,0));
    }

    file_input.close();

}


Files::~Files() {
    // anche se successivamente a questo salvataggio ne dovesse essere chiamato qualcun altro
    // non cambierebbe nulla. L'importante è che, al momento della
    // distruzione, ci sia un punto di salvataggio
    saveAll();
    opened_files.clear();

}
