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

void Command::addArg(QString &arg) {
    _args.push_back(arg);
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

/*
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
}*/

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

    if(!query.exec("SELECT NAME, OWNER FROM FILES WHERE SITEID='"+QString::number(_siteID)+"' AND INVITE = '0'")){
        db.close();
        return false;
    }

    while(query.next()) {
        QString name(query.value("NAME").toString());
        QString owner(query.value("OWNER").toString());
        _args.push_back(QString(owner+"/"+name));
    }
    return true;
}

bool Command::srcCommand(QString &connectionId){

    if(_args.size() != 1)
        return false;

    QSqlDatabase db = QSqlDatabase::database(connectionId+"_filesNEW");
    db.setDatabaseName("db/files.db");

    if (!db.open())
        return false;

    auto pos = _args.first().indexOf("/");
    if (pos == -1) {
        return false;
    }

    QString user = _args.first().split("/").first();
    QString name = _args.first().split("/").last();
    _args.clear();
    QSqlQuery query(db);

    if(!query.exec("SELECT FSNAME FROM FILES WHERE NAME='"+name+"' AND SITEID='"+QString::number(_siteID)+"' AND OWNER='"+user+"' AND INVITE = '0'")){
        db.close();
        return false;
    }

    query.next();
    _args.push_back(query.value("FSNAME").toString());

    return !_args.first().isEmpty();

}

QVector<qint32> Command::renCommand(QString &connectionId) {

    if(_args.size() != 2)
        return QVector<qint32>();

    QVector<qint32 > listId;

    QSqlDatabase db = QSqlDatabase::database(connectionId+"_filesNEW");
    db.setDatabaseName("db/files.db");

    if (!db.open())
        return listId;

    QSqlQuery query(db);
    auto list1 = _args[0].split("/");
    auto list2 = _args[1].split("/");
    if( list1.size()!=2 || list2.size()!=2 || list1.first() != list2.first() ) {
        return listId;
    }

    auto owner = list1.first();
    auto nameOld = list1.last();
    auto nameNew = list2.last();

    if(!query.exec("SELECT SITEID FROM FILES WHERE NAME='"+nameOld+"' AND OWNER='"+owner+"';")){
        db.close();
        return QVector<qint32>();
    }

    while(query.next()){
        qint32 siteId = query.value("SITEID").toInt();
        if(siteId != _siteID)
            listId.push_back(siteId);
    }

    if(!query.exec("UPDATE FILES SET NAME='"+nameNew+"' WHERE NAME='"+nameOld+"' AND OWNER='"+owner+"'")){
        db.rollback();
        db.close();
        return QVector<qint32>();
    }


    return listId;
}


bool Command::rmCommand(QString& connectionId) { //la rmCommand elimina il file per il solo client richiedente

    if(_args.size()!=1)
        return false;

    QString fileName = _args.first();

    QSqlDatabase db = QSqlDatabase::database(connectionId+"_filesNEW");
    db.setDatabaseName("db/files.db");

    auto list = _args[0].split("/");
    QString owner = list.first();
    QString name = list.last();

    if (!db.open())
        return false;

    QSqlQuery query(db);
    if(!query.exec("DELETE FROM FILES WHERE SITEID='"+QString::number(_siteID)+"' AND NAME='"+name+"' AND OWNER='"+owner+"'")){
        db.rollback();
        db.close();
        return false;
    }

    return true;
}

bool Command::svCommand(QString& connectionId) { //la rmCommand elimina il file per il solo client richiedente

    if(_args.size()!=1)
        return false;

    QString fileName = _args.first();

    using namespace std::chrono;
    auto ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    QString serverFileName = connectionId+"_"+_args.first()+"_"+QString::number(ms.count())+".json";

    QSqlDatabase db = QSqlDatabase::database(connectionId+"_filesNEW");
    db.setDatabaseName("db/files.db");

    auto list = _args[0].split("/");
    QString owner = list.first();
    QString name = list.last();

    if (!db.open())
        return false;

    QSqlQuery query(db);
    if(!query.exec("INSERT INTO FILES (SITEID, NAME, OWNER, FSNAME, INVITE) "
                   "VALUES ('"+QString::number(_siteID)+"', '"+name+"', '"+owner+"', '"+serverFileName+"', '0')")){
        db.rollback();
        db.close();
        return false;
    }

    return true;
}


QVector<qint32> Command::rmAllCommand(QString& connectionId) { //la rmAllCommand elimina il file a chiunque

    if(_args.size()!=1)
        return QVector<qint32>();

    QString fileName = _args.first();
    QVector<qint32> listId{};

    QSqlDatabase db = QSqlDatabase::database(connectionId+"_filesNEW");
    db.setDatabaseName("db/files.db");

    auto list = _args[0].split("/");
    QString owner = list.first();
    QString name = list.last();

    if (!db.open())
        return listId;

    QSqlQuery query(db);
    if(!query.exec("SELECT SITEID, FSNAME FROM FILES WHERE NAME='"+name+"' AND OWNER='"+owner+"'")){
        db.close();
        return QVector<qint32>();
    }


    while(query.next()){
        qint32 siteId = query.value("SITEID").toInt();
        if(siteId != _siteID)
            listId.push_back(siteId);
        else
            _args.push_back(query.value("FSNAME").toString());
    }

    if(!query.exec("DELETE FROM FILES WHERE NAME='"+name+"' AND OWNER='"+owner+"'")){
        db.rollback();
        db.close();
        return QVector<qint32>() ;
    }


    return listId;
}


bool Command::inviteCommand(QString &connectionId) {

    if(_args.size() != 3)
        return false;

    QSqlDatabase dbFiles = QSqlDatabase::database(connectionId+"_filesNEW");
    dbFiles.setDatabaseName("db/files.db");

    QSqlDatabase dbUsers = QSqlDatabase::database(connectionId+"_login");
    dbUsers.setDatabaseName("login.db");

    if (!dbFiles.open() || !dbUsers.open())
        return false;

    QString owner = _args.first();
    QString name = _args.at(1);
    QString username = _args.last();
    _args.clear();
    QSqlQuery queryFiles(dbFiles);
    QSqlQuery queryUsers(dbUsers);

    if(!queryUsers.exec("SELECT SITEID FROM LOGIN WHERE USER = '"+username+"';")){
        dbUsers.close();
        return false;
    }

    queryUsers.next();
    auto siteId = queryUsers.value("SITEID").toInt();
    dbUsers.close();

    dbFiles.transaction();
    if(!queryFiles.exec("SELECT FSNAME FROM FILES WHERE SITEID = '"+QString::number(_siteID)+"' AND NAME = '"+name+"' AND OWNER = '"+owner+"';")){
        dbFiles.rollback();
        dbFiles.close();
        return false;
    }

    queryFiles.next();
    auto fsName = queryFiles.value("FSNAME").toString();

    if(!queryFiles.exec("SELECT COUNT(*) FROM FILES WHERE SITEID = '"+QString::number(siteId)+"' AND NAME = '"+name+"' AND OWNER = '"+owner+"';")){
        dbFiles.rollback();
        dbFiles.close();
        return false;
    }

    queryFiles.next();
    if (queryFiles.value("COUNT(*)").toInt() != 0) {
        return true;
    }

    if(!queryFiles.exec("INSERT INTO FILES ('SITEID', 'NAME', 'OWNER', 'FSNAME', 'INVITE') VALUES ('"+QString::number(siteId)+"', '"+name+"', '"+owner+"', '"+fsName+"', '1');")){
        dbFiles.rollback();
        dbFiles.close();
        return false;
    }

    if(!dbFiles.commit()){
        dbFiles.rollback();
        dbFiles.close();
        return false;
    }

    _args.push_back(QString::number(siteId));
    return true;
}

bool Command::lsInviteCommand(QString &connectionId) {
    if(!_args.empty())
        return false;

    QSqlDatabase db = QSqlDatabase::database(connectionId+"_filesNEW");
    db.setDatabaseName("db/files.db");

    if (!db.open())
        return false;

    QSqlQuery query(db);

    if(!query.exec("SELECT NAME, OWNER FROM FILES WHERE SITEID='"+QString::number(_siteID)+"' AND INVITE = '1';")){
        db.close();
        return false;
    }

    while(query.next()) {
        QString name(query.value("NAME").toString());
        QString owner(query.value("OWNER").toString());
        _args.push_back(QString(owner+"/"+name));
    }
    return true;
}


bool Command::ctrlInviteCommand(QString &connectionId) {
    if(_args.size() != 3)
        return false;

    QSqlDatabase db = QSqlDatabase::database(connectionId+"_filesNEW");
    db.setDatabaseName("db/files.db");

    if (!db.open())
        return false;

    QSqlQuery query(db);
    auto mode = _args.first();
    auto user = _args.at(1);
    auto fileName = _args.last();

    if (mode == "accept") {
        if (!query.exec("UPDATE FILES SET INVITE = '0' WHERE SITEID = '"+QString::number(_siteID)+"' AND NAME = '"+fileName+ "' AND OWNER = '" +user+ "';")) {
            db.close();
            return false;
        }
    } else if (mode == "reject") {
        if(!query.exec("DELETE FROM FILES WHERE SITEID = '"+QString::number(_siteID)+"' AND NAME = '"+fileName+"' AND OWNER = '"+user+"';")){
            db.close();
            return false;
        }
    }
    return true;
}