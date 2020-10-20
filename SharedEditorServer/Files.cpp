//
// Created by utente on 01/08/2020.
//

#include <set>
#include <iostream>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include "Files.h"

enum{file,counter,dirty_bit};
QVector<QString> Files::fonts{"Arial","Arial Black","Comic Sans MS", "Courier","Georgia","Impact","Tahoma","Times New Roman","Trebuchet MS","Verdana"};

Files::Files(){
    QDir().mkdir("files");
}

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
        QtLoadFileJson(fileName.toStdString(),std::get<file>(i->second),symbles);
    }
    return symbles;
}

bool Files::closeFile(QString &fileName) {

    auto i = opened_files.find(fileName);
    if ( i!=opened_files.end() ){
        if (--std::get<counter>(i->second) == 0) {
            if (std::get<dirty_bit>(i->second))
                QtSaveFileJson(fileName.toStdString(), std::get<file>(i->second));
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


void Files::aligSymbolInFile(QString &fileName, Symbol &sym) {
    auto i = opened_files.find(fileName);

    if(i != opened_files.end()) {
        auto node = std::get<file>(i->second).extract(sym);
        if( !node.empty() ){
            node.key().setAlignmentType(sym.getAlignmentType());
            std::get<file>(i->second).insert(std::move(node));
            std::get<dirty_bit>(i->second) = true;
        }
    }
}

void Files::saveChanges(QString &fileName) {

    auto i = opened_files.find(fileName);
    if( !std::get<dirty_bit>(i->second) )
        return;
    QtSaveFileJson(fileName.toStdString(), std::get<file>(i->second));

}

void Files::saveAll() {

    for( auto of: opened_files ) {
        if (!std::get<dirty_bit>(of.second))
            continue;
        QtSaveFileJson(of.first.toStdString(), std::get<file>(of.second));
    }
}


void Files::QtSaveFileJson(const std::string& f, std::map<Symbol,int>& symbles){
    QJsonArray syms;

    for(auto& itr:symbles) {
        QJsonObject symbol;
        QJsonObject symId;
        symbol["char"] = (int)itr.first.getValue().unicode();
        symbol["font"] = fonts.indexOf(itr.first.getFormat().fontFamily());
        symbol["size"] = itr.first.getFormat().font().pointSize();
        int rgb = itr.first.getFormat().foreground().color().red();
        rgb<<=8;
        rgb |= itr.first.getFormat().foreground().color().green();
        rgb<<=8;
        rgb |= itr.first.getFormat().foreground().color().blue();
        symbol["color"] = rgb;
        symbol["underline"] = itr.first.getFormat().fontUnderline();
        symbol["bold"] = itr.first.getFormat().font().bold();
        symbol["italic"] = itr.first.getFormat().fontItalic();
        if( itr.second == -1 || itr.first.getValue().unicode() == 8233 )
            symbol["alignment"] = (int)itr.first.getAlignmentType();
        else
            symbol["alignment"] = -1;

        QJsonArray pos;
        for(auto i: itr.first.getPos()){
            QJsonValue val((int)i);
            pos.append(val);
        }
        symbol["pos"]=pos;

        symId["siteId"] = itr.first.getSymId().getSiteId();
        symId["count"] = itr.first.getSymId().getCount();
        symbol["symId"] = symId;

        syms.append(symbol);
    }

    QJsonDocument json(syms);
    QFile file(QString::fromStdString("./files/"+f));
    file.open(QIODevice::WriteOnly);
    file.startTransaction();
    file.write(json.toJson());
    file.commitTransaction();
    file.close();

}

void Files::QtLoadFileJson(std::string f,std::map<Symbol,int>& symbles, std::shared_ptr<std::vector<Symbol>> syms){

    QFile file(QString::fromStdString("./files/"+f));
    if(!file.exists()){
        std::vector<quint32> v = {0};
        QTextCharFormat frmt;
        Symbol s('0',-1,-1,v,frmt,0);
        symbles.insert(std::make_pair(s, -1));
        syms->push_back(s);
    }

    file.open(QIODevice::ReadOnly);
    file.startTransaction();
    auto arr = file.readAll();
    file.commitTransaction();
    file.close();

    QJsonDocument json = QJsonDocument::fromJson(arr);
    auto symsJson = json.array();

    for(int i=0; i<symsJson.size(); i++){
        QJsonValue symbol = symsJson[i];
        QTextCharFormat frmt;
        short align;
        std::vector<quint32> pos;
        qint32 siteId;
        quint32 counter;

        QChar ch((short)symbol["char"].toInt());
        int indx = symbol["font"].toInt();
        frmt.setFontFamily(fonts[ indx<0 ? 7: indx]);
        frmt.setFontPointSize(symbol["size"].toInt());
        uint rgb = (uint)symbol["color"].toInt();
        frmt.setForeground(QBrush(QColor(rgb)));
        frmt.setFontUnderline(symbol["underline"].toBool());
        frmt.setFontWeight(symbol["bold"].toBool()? QFont::Bold : QFont::Normal );
        frmt.setFontItalic(symbol["italic"].toBool());
        align = (short)symbol["alignment"].toInt();
        auto jpos = symbol["pos"].toArray();

        for(auto i: jpos)
            pos.push_back((quint32)i.toInt());

        auto symId = symbol["symId"];
        siteId = symId["siteId"].toInt();
        counter = (quint32)symId["count"].toInt();

        Symbol s(ch,siteId,counter,pos,frmt,align);
        int marker = 0;
        if( siteId == -1 && counter == -1)
            marker = -1;
        symbles.insert(std::make_pair(s,marker));
        syms->push_back(s);
    }

}

Files::~Files() {
    // anche se successivamente a questo salvataggio ne dovesse essere chiamato qualcun altro
    // non cambierebbe nulla. L'importante è che, al momento della
    // distruzione, ci sia un punto di salvataggio
    saveAll();
    opened_files.clear();

}
