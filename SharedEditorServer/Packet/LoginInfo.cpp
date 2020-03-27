//
// Created by utente on 17/03/2020.
//

#include "LoginInfo.h"

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

void LoginInfo::setType(qint32 type) {
    _type = type;
}
