//
// Created by utente on 17/03/2020.
//


#include <QSqlDatabase>
#include <QtWidgets/QMessageBox>
#include "LoginInfo.h"
#include <QSqlQuery>
#include <QtCore/QVariant>


LoginInfo::LoginInfo(qint32 siteId, type_t type, QString user, QString password) : Payload(siteId),
                                                                                   _user(std::move(user)),
                                                                                   _type(type),
                                                                                   _password(std::move(password)) {}

QString &LoginInfo::getUser(){
    return _user;
}

void LoginInfo::setUser( QString user) {
    _user = user;
}

QString &LoginInfo::getPassword() {
    return _password;
}

void LoginInfo::setPassword( QString password) {
    _password = password;
}

LoginInfo::type_t LoginInfo::getType() {
    return _type;
}

void LoginInfo::setType(type_t type) {
    _type = type;
}

qint32 LoginInfo::login(const QString& connectionId) {
    QSqlDatabase db = QSqlDatabase::database(connectionId+"_login");
    db.setDatabaseName("login.db");

    if (!db.open())
        return -1;

    QSqlQuery query(db);
    if(!query.exec("SELECT PASS, SITEID FROM LOGIN WHERE USER='"+_user+"'"))
        return -1;

    db.close();

    if(query.first()) {
        if (_password == query.value("PASS").toString()) {
            _type = LoginInfo::login_ok;
            _siteID = query.value("SITEID").toInt();
            return _siteID;
        } else {
            _type = LoginInfo::login_error;
            _siteID = -1;
            _user = "";
            _password = "";
            return -1;
        }
    }else {
        _type = LoginInfo::login_error;
        _siteID = -1;
        _user = "";
        _password = "";
        return -1;
    }
}