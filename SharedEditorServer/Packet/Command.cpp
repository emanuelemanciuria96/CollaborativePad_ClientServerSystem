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
    DBSql sqldb("ciao_directories.db");
    sqldb.openDB();
    std::string query;

    query = "SELECT * FROM DIRECTORIES WHERE DIRECTORY LIKE '"+directory.left(directory.size()-3).toStdString()+"%"+std::to_string(directory.right(1).toUInt()+1)+"'";
    sqldb.query(query);

    return sqldb.getResult()["DIRECTORY"];
}

bool Command::removeDirectory(QString &directory) {
    return false;
}


