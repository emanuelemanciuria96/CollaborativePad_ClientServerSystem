//
// Created by utente on 17/03/2020.
//


#include <QSqlDatabase>
#include <QtWidgets/QMessageBox>
#include "LoginInfo.h"
#include <QSqlQuery>
#include <QtCore/QVariant>
#include <iostream>
#include <QtCore/QFile>


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

qint32 LoginInfo::login(const QString& connectionId) {
    QSqlDatabase db = QSqlDatabase::database(connectionId+"_login");
    db.setDatabaseName("login.db");

    if (!db.open())
        return -1;

    QSqlQuery query(db);
    if(!query.exec("SELECT PASS, SITEID, IMAGE, NAME, EMAIL FROM LOGIN WHERE USER='"+_user+"'"))
        return -1;

    db.close();

    if(query.first()) {
        if (_password == query.value("PASS").toString()) {
            _type = LoginInfo::login_ok;
            _siteID = query.value("SITEID").toInt();
            _image = QPixmap(query.value("IMAGE").toString());
            _name = query.value("NAME").toString();
            _email = query.value("EMAIL").toString();
            std::cout << _name.toStdString() << std::endl;
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

bool LoginInfo::updateInfo(const QString& connectionId) {
    QSqlDatabase db = QSqlDatabase::database(connectionId+"_login");
    db.setDatabaseName("login.db");

    if (!db.open())
        return false;

    QString fileName("images/"+QString::number(_siteID)+".jpg");
    QSqlQuery query(db);
    if(!query.exec("UPDATE LOGIN SET IMAGE = '"+fileName+"', NAME = '"+_name+"', EMAIL = '"+_email+"' WHERE SITEID = '"+QString::number(_siteID)+"';"))
        return false;

    _image.save(fileName, "JPG");
    db.close();

    return true;
}