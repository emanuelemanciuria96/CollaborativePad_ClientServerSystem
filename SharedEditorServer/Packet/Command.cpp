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

/*QString Command::opnCommand(QString &connectionId){
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
}*/

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

bool Command::opnCommand(QString &connectionId){
    if(_args.size() != 1)
        return false;

    QSqlDatabase db = QSqlDatabase::database(connectionId+"_filesNEW");
    db.setDatabaseName("db/files.db");

    if (!db.open())
        return false;

    auto pos = _args.first().indexOf("/");
    if (pos == -1) {
        QString name = _args.first();
        _args.clear();
        QSqlQuery query(db);

        if(!query.exec("SELECT FSNAME FROM FILES WHERE NAME='"+name+"' AND SITEID='"+QString::number(_siteID)+"' AND OWNER='#'")){
            db.close();
            return false;
        }

        query.next();
        _args.push_back(query.value("FSNAME").toString());

        return !_args.first().isEmpty();

    }

    auto list = _args.first().split("/");
    QString owner = list.first();
    QString name = list.last();
    _args.clear();
    QSqlQuery query(db);

    if(!query.exec("SELECT FSNAME FROM FILES WHERE NAME='"+name+"' AND SITEID='"+QString::number(_siteID)+"' AND OWNER='"+owner+"'")){
        db.close();
        return false;
    }

    query.next();
    _args.push_back(query.value("FSNAME").toString());

    return !_args.first().isEmpty();

}
