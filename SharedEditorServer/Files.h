//
// Created by utente on 01/08/2020.
//

#ifndef SHAREDEDITORSERVER_FILES_H
#define SHAREDEDITORSERVER_FILES_H


#include <QtCore/QString>
#include <map>
#include <vector>
#include "Packet/Symbols/Symbol.h"
#include <QtCore/QFile>
#include "json/json.h"
#include <fstream>
#include <shared_mutex>


class Files {
public:
    Files() = default;
    ~Files();
    std::shared_ptr<std::vector<Symbol>> openFile(QString& fileName);
    bool closeFile(QString& fileName);
    bool deleteFile(QString &fileName);
    void addSymbolInFile(QString& fileName, Symbol& sym);
    void rmvSymbolInFile(QString& fileName, Symbol& sym);
    void saveChanges(QString& fileName);
    void saveAll();

private:
    std::map< QString,std::tuple< std::map<Symbol,int>,quint32,bool> > opened_files;

    static void saveFileJson(std::string dir,std::map<Symbol,int>& symbles);
    static void loadFileJson(std::string dir,std::map<Symbol,int>& symbles,std::shared_ptr<std::vector<Symbol>> syms);
    static void QTsaveFileJson(const std::string& dir,std::vector<Symbol> _symbols);


};


#endif //SHAREDEDITORSERVER_FILES_H
