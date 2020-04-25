//
// Created by utente on 01/04/2020.
//

#include "Command.h"
#include "../database/DBSql.h"

#include <utility>

Command::Command(qint32 siteId, Command::cmd_t cmd, QVector<QString> args) : Payload(siteId), _cmd(cmd),
                                                                                    _args(std::move(args)) {}

Command::cmd_t Command::getCmd() const {
    return _cmd;
}

void Command::setCmd(Command::cmd_t cmd) {
    this->_cmd = cmd;
}

const QVector<QString> &Command::getArgs() const {
    return _args;
}

void Command::setArgs(const QVector<QString> &args) {
    _args = args;
}

const QString &Command::getCurrentDirectory() const {
    return _currentDirectory;
}

void Command::setCurrentDirectory(const QString &directory) {
    _currentDirectory = directory;
}

QVector<QString> Command::getDirectories(QString& user, QString& directory) {
    QVector<QString> directories;
    QString local;
    DBSql sqldb("ciao_directories.db");
    sqldb.openDB();
    std::string query;
    int count = 0;
    int i = 0;

    query = "SELECT * FROM DIRECTORIES";
    sqldb.query(query);
    if(sqldb.getResult().find("DIRECTORY") == sqldb.getResult().end())
        return directories;

    if(!directory.endsWith("/"))
        local = directory+"/";
    else
        local = directory;

    while((i = local.indexOf("/", i)) != -1) {
        ++count;
        i++;
    }
    directories = sqldb.getResult()["DIRECTORY"];
    for(const auto& s: directories){
        std::cout << s.toStdString() << std::endl;
    }
    directories.erase(std::remove_if(directories.begin(), directories.end(), [local, count](const QString& str) {
        int j = 0;
        int k = 0;
        while ((j = str.indexOf("/", j)) != -1) {
            ++j;
            k++;
        }
        return (k>count || !str.startsWith(local));
    }), directories.end());

    return directories;
}


