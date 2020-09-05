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
    std::vector<Symbol> openFile(QString& fileName);
    void closeFile(QString& fileName);
    void deleteFile(QString &fileName);
    void addSymbolInFile(QString& fileName, Symbol& sym);
    void rmvSymbolInFile(QString& fileName, Symbol& sym);
    void saveChanges(QString& fileName);
    void saveAll();

private:
    std::shared_mutex files_mtx;
    std::map< QString,std::tuple< std::vector<Symbol>,quint32,std::shared_mutex*,bool> > opened_files;

    static void saveFileJson(std::string dir,std::vector<Symbol>& symbles);
    static void loadFileJson(std::string dir,std::vector<Symbol>& symbles);
    static void QTsaveFileJson(const std::string& dir,std::vector<Symbol> _symbols);


};


#endif //SHAREDEDITORSERVER_FILES_H
