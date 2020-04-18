//
// Created by utente on 17/03/2020.
//

#include "LoginInfo.h"

#include <utility>

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
