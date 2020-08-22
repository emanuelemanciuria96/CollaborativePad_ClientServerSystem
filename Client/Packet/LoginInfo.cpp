//
// Created by utente on 17/03/2020.
//

#include "LoginInfo.h"

#include <utility>
#include <QtCore/QCryptographicHash>

LoginInfo::LoginInfo(qint32 siteId, LoginInfo::type_t type,QString user, QString password) : Payload(
        siteId), _user(std::move(user)), _password(std::move(password)), _type(type) {
    _image = QPixmap();
    _name = QString();
    _email = QString();
}

QString &LoginInfo::getUser(){
    return _user;
}

void LoginInfo::setUser( QString user) {
    _user = std::move(user);
}

QString &LoginInfo::getPassword() {
    return _password;
}

void LoginInfo::setPassword( QString password) {
    _password = std::move(password);
}

LoginInfo::type_t LoginInfo::getType() {
    return _type;
}

void LoginInfo::setType(type_t type) {
    _type = type;
}

const QPixmap &LoginInfo::getImage() const {
    return _image;
}

void LoginInfo::setImage(const QPixmap &image) {
    _image = image;
}

const QString &LoginInfo::getName() const {
    return _name;
}

void LoginInfo::setName(const QString &name) {
    _name = name;
}

const QString &LoginInfo::getEmail() const {
    return _email;
}

void LoginInfo::setEmail(const QString &email) {
    _email = email;
}
