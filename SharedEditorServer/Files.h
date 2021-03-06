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
#include <fstream>
#include <shared_mutex>


class Files {
public:
    Files();
    ~Files();
    std::shared_ptr<std::vector<Symbol>> openFile(QString& fileName);
    bool closeFile(QString& fileName);
    bool deleteFile(QString &fileName);
    void addSymbolInFile(QString& fileName, Symbol& sym);
    void rmvSymbolInFile(QString& fileName, Symbol& sym);
    void modSymbolInFile(QString& fileName, Symbol& sym);
    void aligSymbolInFile(QString& fileName, Symbol& sym);
    void saveAll();

private:
    std::map< QString,std::tuple< std::map<Symbol,int>,quint32,bool> > opened_files;
    static QVector<QString> fonts;

    static void QtSaveFileJson(const std::string& f, std::map<Symbol,int>& symbles);
    static void QtLoadFileJson(std::string f,std::map<Symbol,int>& symbles,std::shared_ptr<std::vector<Symbol>> syms);


};


#endif //SHAREDEDITORSERVER_FILES_H
