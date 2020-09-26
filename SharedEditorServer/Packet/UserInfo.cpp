//
// Created by utente on 18/09/2020.
//

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QPixmap>
#include <QVariant>
#include "UserInfo.h"

bool UserInfo::obtainImage(QString &connectionId) {
    auto db = QSqlDatabase::database(connectionId+"_login");
    db.setDatabaseName("db/login.db");

    if (!db.open()) {
        return false;
    }

    QSqlQuery query(db);
    if(!query.exec("SELECT IMAGE FROM LOGIN WHERE USER='"+_username+"'"))
        return false;

    db.close();

    if(query.first())
        _image = QPixmap(query.value("IMAGE").toString());
    else
        return false;

    return true;
}

bool UserInfo::obtainUser(QString &connectionId) {
    auto db = QSqlDatabase::database(connectionId+"_login");
    db.setDatabaseName("db/login.db");

    if (!db.open()) {
        return false;
    }

    QSqlQuery query(db);
    if(!query.exec("SELECT USER FROM LOGIN WHERE SITEID='"+QString::number(_siteID)+"'"))
        return false;

    db.close();

    if(query.first())
        _username = query.value("USER").toString();
    else
        return false;

    return true;
}
