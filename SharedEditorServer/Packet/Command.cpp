//
// Created by utente on 01/04/2020.
//

#include "Command.h"
#include "../database/DBSql.h"

#include <utility>
#include <QtCore/QDir>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QVariant>

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

bool Command::mkdirCommand(QString& connectionId, QString& user) {
    if(_args.size()!=1)
        return false;

    QSqlDatabase db = QSqlDatabase::database(connectionId);
    db.setDatabaseName(user+"_directories.db");

    if (!db.open())
        return false;

    QString currentDir(_args.first());
    currentDir.truncate(currentDir.lastIndexOf("/"));
    QString newDir(_args.first()+">D");

    QSqlQuery query(db);
    if(!query.exec("INSERT INTO DIRECTORIES ('DIRECTORY', 'SUBF') VALUES ('"+currentDir+"', '"+newDir+"');")){
        db.close();
        return false;
    }

    db.close();
    return true;
}

/*LE FUNZIONI CHE SEGUONO SONO TUTTE DA RIFARE*/

QVector<QString> Command::openCommand(QString& connectionId, QString& user, QString& directory) {
    QVector<QString> directories;
    QSqlDatabase db = QSqlDatabase::database(connectionId);
    db.setDatabaseName(user+"_directories.db");

    if (!db.open())
        return directories;

    QSqlQuery query(db);
    if(!query.exec("SELECT * FROM DIRECTORIES WHERE DIRECTORY LIKE '"+directory.left(directory.size()-3)+"/%"+QString::number(directory.right(1).toUInt()+1)+"'"))
    {
        db.close();
        return directories;
    }

    while(query.next()){
        directories.push_back(query.value("DIRECTORY").toString());
    }

    db.close();
    return directories;
}

bool Command::removeDirectory(QString& connectionId, QString& user, QString &directory) {
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

bool Command::makeDirectory(QString& connectionId, QString& user, QString &directory) {
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

bool Command::copyFile(QString& connectionId, QString& user, QString &src, QString &dest) {
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

bool Command::moveFile(QString& connectionId, QString& user, QString& src, QString& dest) {
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




