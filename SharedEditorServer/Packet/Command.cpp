//
// Created by utente on 01/04/2020.
//

#include "Command.h"
#include <utility>
#include <QtCore/QDir>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QVariant>
#include <iostream>

Command::Command(qint32 siteId, cmd_t cmd, QVector<QString> args) : Payload(siteId), _cmd(cmd),
                                                                    _args(std::move(args)) {}

Command::cmd_t Command::getCmd() const {
    return _cmd;
}

void Command::setCmd(Command::cmd_t cmd) {
    _cmd = cmd;
}

const QVector<QString> &Command::getArgs() const {
    return _args;
}

void Command::setArgs(const QVector<QString> &args) {
    _args = args;
}

bool Command::cdCommand(QString& connectionId){
    if(_args.size()!=1)
        return false;

    QSqlDatabase db = QSqlDatabase::database(connectionId+"_directories");
    db.setDatabaseName("directories.db");

    if (!db.open())
        return false;

    QString dir = _args.first();
    _args.clear();
    QSqlQuery query(db);

    if(!query.exec("SELECT SUBF FROM DIRECTORIES WHERE DIRECTORY='"+dir+"' AND SITEID='"+QString::number(_siteID)+"'")){
        db.close();
        return false;
    }

    while(query.next())
        _args.push_back(query.value("SUBF").toString());

    return true;
}

bool Command::mkdirCommand(QString& connectionId) {
    if(_args.size()!=1)
        return false;

    QSqlDatabase db = QSqlDatabase::database(connectionId+"_directories");
    db.setDatabaseName("directories.db");

    if (!db.open())
        return false;

    QString currentDir(_args.first());
    currentDir.truncate(currentDir.lastIndexOf("/"));
    QString newDir(_args.first()+">D");

    QSqlQuery query(db);
    if(!query.exec("INSERT INTO DIRECTORIES ('SITEID', 'DIRECTORY', 'SUBF') VALUES ('"+QString::number(_siteID)+"', '"+currentDir+"', '"+newDir+"');")){
        db.close();
        return false;
    }

    db.close();
    return true;
}

bool Command::rmCommand(QString& connectionId) {
    if(_args.size()!=1)
        return false;

    QChar type(_args.first().back());

    if(type == "D"){
        return rmDir(connectionId);
    } else if(type == "F"){
        return rmFile(connectionId);
    }

    return false;
}

bool Command::rmDir(QString &connectionId) {
    if(_args.size()!=1)
        return false;

    QSqlDatabase dbDirs = QSqlDatabase::database(connectionId+"_directories");
    QSqlDatabase dbFiles = QSqlDatabase::database(connectionId+"_files");
    dbDirs.setDatabaseName("directories.db");
    dbFiles.setDatabaseName("files.db");

    if (!dbDirs.open() || !dbFiles.open())
        return false;

    QString dir = _args.first();
    dir.truncate(dir.lastIndexOf(">"));
    QSqlQuery dirQuery(dbDirs);
    QSqlQuery fileQuery(dbFiles);

    QVector<QString> files;

    dbFiles.transaction();
    fileQuery.exec("SELECT FILEID FROM FILES WHERE DIR LIKE '"+dir+"/"+"%' AND SITEID='"+QString::number(_siteID)+"'");

    while (fileQuery.next()) {
        files.push_back(fileQuery.value("FILEID").toString());
    }

    if(!dirQuery.exec("DELETE FROM DIRECTORIES WHERE SUBF='"+dir+">D"+"' OR DIRECTORY='"+dir+"' AND SITEID='"+QString::number(_siteID)+"'")){
        dbFiles.rollback();
        dbFiles.close();
        dbDirs.close();
        return false;
    }
    fileQuery.exec("DELETE FROM FILES WHERE DIR LIKE '"+dir+"/"+"%' AND SITEID='"+QString::number(_siteID)+"'");
    if(!dbFiles.commit()){
        dbFiles.rollback();
        dbFiles.close();
        dbDirs.close();
        return false;
    }

    dbFiles.close();
    dbDirs.close();

    for(const auto& f: files)
        QFile::remove(f);

    return true;
}

bool Command::rmFile(QString &connectionId) {
    if(_args.size()!=1)
        return false;

    QSqlDatabase dbDirs = QSqlDatabase::database(connectionId+"_directories");
    QSqlDatabase dbFiles = QSqlDatabase::database(connectionId+"_files");
    dbDirs.setDatabaseName("directories.db");
    dbFiles.setDatabaseName("files.db");
    QString fileDir(_args.first());

    if (!dbDirs.open() || !dbFiles.open())
        return false;

    QSqlQuery dirQuery(dbDirs);
    QSqlQuery fileQuery(dbFiles);

    if(!fileQuery.exec("SELECT FILEID FROM FILES WHERE DIR='"+fileDir+"' AND SITEID='"+QString::number(_siteID)+"'")){
        dbFiles.close();
        dbDirs.close();
        return false;
    }

    if(!fileQuery.first()){
        dbFiles.close();
        dbDirs.close();
        return false;
    }

    QFile file(fileQuery.value("FILEID").toString());
    dbFiles.transaction();
    fileQuery.exec("DELETE FROM FILES WHERE DIR='"+fileDir+"' AND SITEID='"+QString::number(_siteID)+"'");

    if(!dirQuery.exec("DELETE FROM DIRECTORIES WHERE SUBF='"+fileDir+"' AND SITEID='"+QString::number(_siteID)+"'")){
        dbFiles.rollback();
        dbFiles.close();
        dbDirs.close();
        return false;
    }

    if(!dbFiles.commit()){
        dbFiles.rollback();
        dbFiles.close();
        dbDirs.close();
        return false;
    }

    file.remove();
    return true;
}

QString Command::opnCommand(QString &connectionId){
    QString fileName{};

    if(_args.size()!=1)
        return fileName;

    QSqlDatabase db = QSqlDatabase::database(connectionId+"_files");
    db.setDatabaseName("files.db");

    if (!db.open())
        return fileName;

    QString filePath = _args.first();
    QSqlQuery query(db);

    if(!query.exec("SELECT FILEID FROM FILES WHERE DIR='"+filePath+"' AND SITEID='"+QString::number(_siteID)+"'")){
        db.close();
        return fileName;
    }

    query.next();
    fileName = query.value("FILEID").toString();

    return fileName;
}

bool Command::treeCommand(QString &connectionId) {
    if(!_args.empty())
        return false;

    QSqlDatabase db = QSqlDatabase::database(connectionId+"_directories");
    db.setDatabaseName("directories.db");

    if (!db.open())
        return false;

    QSqlQuery query(db);

    if(!query.exec("SELECT SUBF FROM DIRECTORIES WHERE SITEID='"+QString::number(_siteID)+"'")){
        db.close();
        return false;
    }

    while(query.next())
        _args.push_back(query.value("SUBF").toString());

    return true;
}

/***** FUNZIONI COMMAND PER TABELLE NUOVE *****/

bool Command::lsCommand(QString &connectionId) {
    if(!_args.empty())
        return false;

    QSqlDatabase db = QSqlDatabase::database(connectionId+"_filesNEW");
    db.setDatabaseName("db/files.db");

    if (!db.open())
        return false;

    QSqlQuery query(db);

    if(!query.exec("SELECT NAME, OWNER FROM FILES WHERE SITEID='"+QString::number(_siteID)+"'")){
        db.close();
        return false;
    }

    while(query.next()) {
        QString name(query.value("NAME").toString());
        QString owner(query.value("OWNER").toString());
        if (owner != "#")
            _args.push_back(QString(owner+"/"+name));
        else
            _args.push_back(name);
    }
    return true;
}

/*LE FUNZIONI CHE SEGUONO SONO TUTTE DA RIFARE*/

/*
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
}*/
