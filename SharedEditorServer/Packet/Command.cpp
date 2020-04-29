//
// Created by utente on 01/04/2020.
//

#include "Command.h"
#include "../database/DBSql.h"

#include <utility>
#include <QtCore/QDir>

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
    DBSql sqldb(user.toStdString()+"_directories.db");
    sqldb.openDB();
    std::string query;

    query = "SELECT * FROM DIRECTORIES WHERE DIRECTORY LIKE '"+directory.left(directory.size()-3).toStdString()+"%"+std::to_string(directory.right(1).toUInt()+1)+"'";
    sqldb.query(query);

    return sqldb.getResult()["DIRECTORY"];
}

bool Command::removeDirectory(QString& user, QString &directory) {
    DBSql sqldb(user.toStdString()+"_directories.db");
    sqldb.openDB();
    std::string query;

    query = "DELETE FROM DIRECTORIES WHERE DIRECTORY='"+directory.toStdString()+"'";
    sqldb.query(query);

    query = "SELECT * FROM DIRECTORIES WHERE DIRECTORY='"+directory.toStdString()+"'";
    sqldb.query(query);

    if(directory.at(directory.size()-2) == "F"){
        QFile file(directory.left(directory.size() - 3));
        return (sqldb.getResult()["DIRECTORY"].isEmpty() && file.remove());
    }else if(directory.at(directory.size()-2) == "D"){
        QDir dir(directory.left(directory.size() - 3));
        return (sqldb.getResult()["DIRECTORY"].isEmpty() && dir.removeRecursively());
    }

    return false;
}

bool Command::makeDirectory(QString& user, QString &directory) {
    QDir dir;

    if(dir.mkdir(directory.left(directory.size() - 3))){
        DBSql sqldb(user.toStdString()+"_directories.db");
        sqldb.openDB();
        std::string query;

        query = "INSERT INTO DIRECTORIES ('DIRECTORY') VALUES ('"+directory.toStdString()+"');";
        sqldb.query(query);

        query = "SELECT * FROM DIRECTORIES WHERE DIRECTORY='"+directory.toStdString()+"'";
        sqldb.query(query);

        return !sqldb.getResult()["DIRECTORY"].isEmpty();
    }else{
        return false;
    }
}

bool Command::copyFile(QString& user, QString &src, QString &dest) {
    DBSql sqldb(user.toStdString()+"_directories.db");
    sqldb.openDB();
    std::string query;

    if(src.at(src.size()-2) != "F" || dest.at(dest.size()-2) != "F")
        return false;

    query = "SELECT * FROM DIRECTORIES WHERE DIRECTORY='"+dest.toStdString()+"'";
    sqldb.query(query);

    QFile file(dest.left(dest.size() - 3));

    if(!sqldb.getResult()["DIRECTORY"].isEmpty() && file.exists())
        return true;

    query = "SELECT * FROM DIRECTORIES WHERE DIRECTORY='"+src.toStdString()+"'";
    sqldb.query(query);

    if(sqldb.getResult()["DIRECTORY"].isEmpty()) {
        QFile srcFile(src.left(src.size() - 3));
        srcFile.remove();
        return false;
    }

    if(QFile::copy(src.left(src.size() - 3), dest.left(dest.size() - 3))){
        query = "INSERT INTO DIRECTORIES ('DIRECTORY') VALUES ('"+dest.toStdString()+"');";
        sqldb.query(query);

        query = "SELECT * FROM DIRECTORIES WHERE DIRECTORY='"+dest.toStdString()+"'";
        sqldb.query(query);

        return !sqldb.getResult()["DIRECTORY"].isEmpty();
    }
    return false;
}

bool Command::moveFile(QString& user, QString& src, QString& dest) {
    DBSql sqldb(user.toStdString()+"_directories.db");
    sqldb.openDB();
    std::string query;

    if(src.at(src.size()-2) != "F" || dest.at(dest.size()-2) != "F")
        return false;

    query = "SELECT * FROM DIRECTORIES WHERE DIRECTORY='"+dest.toStdString()+"'";
    sqldb.query(query);

    QFile destFile(dest.left(dest.size() - 3));

    if(!sqldb.getResult()["DIRECTORY"].isEmpty() && destFile.exists()){
        query = "DELETE FROM DIRECTORIES WHERE DIRECTORY='"+src.toStdString()+"'";
        sqldb.query(query);

        QFile srcFile(src.left(src.size() - 3));
        srcFile.remove();
        return true;
    }

    query = "SELECT * FROM DIRECTORIES WHERE DIRECTORY='"+src.toStdString()+"'";
    sqldb.query(query);

    if(sqldb.getResult()["DIRECTORY"].isEmpty()){
        QFile srcFile(src.left(src.size() - 3));
        srcFile.remove();
        return false;
    }

    if(QFile::copy(src.left(src.size() - 3), dest.left(dest.size() - 3))){
        query = "INSERT INTO DIRECTORIES ('DIRECTORY') VALUES ('"+dest.toStdString()+"');";
        sqldb.query(query);

        query = "SELECT * FROM DIRECTORIES WHERE DIRECTORY='"+dest.toStdString()+"'";
        sqldb.query(query);

        if(!sqldb.getResult()["DIRECTORY"].isEmpty()) {
            query = "DELETE FROM DIRECTORIES WHERE DIRECTORY='"+src.toStdString()+"'";
            sqldb.query(query);
            QFile srcFile(src.left(src.size() - 3));
            srcFile.remove();
        }

        return !sqldb.getResult()["DIRECTORY"].isEmpty();
    }
    return false;
}




