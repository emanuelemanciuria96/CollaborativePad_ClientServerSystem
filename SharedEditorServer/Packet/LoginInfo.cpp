//
// Created by utente on 17/03/2020.
//


#include "LoginInfo.h"
#include "../database/DBSql.h"


LoginInfo::LoginInfo(qint32 siteId, qint32 type, const QString user, const QString password) : Payload(siteId),
                                                                                                 _user(user),
                                                                                                 _type(type),
                                                                                                 _password(password) {}

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

qint32 LoginInfo::getType() {
    return _type;
}

void LoginInfo::setType(type_t type) {
    _type = type;
}

qint32 LoginInfo::login() {
    DBSql sqldb("login.db");
    sqldb.openDB();
    std::string query;

    query = "SELECT * FROM LOGIN WHERE USER='"+_user.toStdString()+"'";
    sqldb.query(query);
    sqldb.closeDB();
    if(_password.toStdString() == sqldb.getResult()["PASS"]) {
        _type = LoginInfo::login_ok;
        _siteID = std::stoi(sqldb.getResult()["SITEID"]);
        _user = "";
        _password = "";
        return _siteID;
    } else {
        _type = LoginInfo::login_error;
        _siteID = -1;
        _user = "";
        _password = "";
        return -1;
    }
}