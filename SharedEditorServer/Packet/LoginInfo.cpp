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
                                                                                   _password(std::move(password)){
    _image = QPixmap();
    _name = QString();
    _email = QString();
}

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

bool LoginInfo::login(const QString& connectionId) {
    QSqlDatabase db = QSqlDatabase::database(connectionId+"_login");
    db.setDatabaseName("db/login.db");

    if (!db.open()) {
        _type = LoginInfo::login_error;
        _siteID = -1;
        _user = "";
        _password = "";
        return false;
    }

    QSqlQuery query(db);
    if(!query.exec("SELECT PASS, SITEID, IMAGE, NAME, EMAIL FROM LOGIN WHERE USER='"+_user+"'")) {
        db.close();
        _type = LoginInfo::login_error;
        _siteID = -1;
        _user = "";
        _password = "";
        return false;
    }

    db.close();

    if(query.first()) {
        if (_password == query.value("PASS").toString()) {
            _type = LoginInfo::login_ok;
            _siteID = query.value("SITEID").toInt();
            _image = QPixmap(query.value("IMAGE").toString());
            _name = query.value("NAME").toString();
            _email = query.value("EMAIL").toString();
            std::cout << _name.toStdString() << std::endl;
            return true;
        } else {
            _type = LoginInfo::login_error;
            _siteID = -1;
            _user = "";
            _password = "";
            return false;
        }
    }else {
        _type = LoginInfo::login_error;
        _siteID = -1;
        _user = "";
        _password = "";
        return false;
    }
}

bool LoginInfo::updateInfo(const QString& connectionId) {
    QSqlDatabase db = QSqlDatabase::database(connectionId+"_login");
    db.setDatabaseName("db/login.db");

    if (!db.open())
        return false;

    QString fileName("");

    if (!_image.isNull())
        fileName = "images/"+QString::number(_siteID)+".jpg";

    QSqlQuery query(db);
    if(!query.exec("UPDATE LOGIN SET IMAGE = '"+fileName+"', NAME = '"+_name+"', EMAIL = '"+_email+"' WHERE SITEID = '"+QString::number(_siteID)+"';")) {
        db.close();
        return false;
    }

    if (!_image.isNull())
        _image.save(fileName, "JPG");
    db.close();

    return true;
}

bool LoginInfo::signup(const QString &connectionId) {
    QSqlDatabase db = QSqlDatabase::database(connectionId+"_login");
    db.setDatabaseName("db/login.db");

    if (!db.open()) {
        _type = LoginInfo::signup_error;
        _siteID = -1;
        _user = "";
        _password = "";
        _image = QPixmap();
        _name = "";
        _email = "";
        return false;
    }

    QString fileName("");

    QSqlQuery query(db);

    db.transaction();
    if(!query.exec("SELECT MAX(SITEID) FROM LOGIN;")) {
        db.rollback();
        db.close();
        _type = LoginInfo::signup_error;
        _siteID = -1;
        _user = "";
        _password = "";
        _image = QPixmap();
        _name = "";
        _email = "";
        return false;
    }

    query.next();
    _siteID = query.value("MAX(SITEID)").toInt();
    _siteID++;

    if (!_image.isNull())
        fileName = "images/"+QString::number(_siteID)+".jpg";

    if(!query.exec("INSERT INTO LOGIN VALUES ('"+_user+"', '"+_password+"', '"+QString::number(_siteID)+"', '"+fileName+"', '"+_name+"', '"+_email+"');")) {
        db.rollback();
        db.close();
        _type = LoginInfo::signup_error;
        _siteID = -1;
        _user = "";
        _password = "";
        _image = QPixmap();
        _name = "";
        _email = "";
        return false;
    }

    if (!_image.isNull())
        _image.save(fileName, "JPG");

    if(!db.commit()){
        db.rollback();
        db.close();
        _type = LoginInfo::signup_error;
        _siteID = -1;
        _user = "";
        _password = "";
        _image = QPixmap();
        _name = "";
        _email = "";
        return false;
    }

    _type = LoginInfo::signup_ok;
    db.close();
    return true;
}

bool LoginInfo::searchUser(const QString &connectionId) {
    QSqlDatabase db = QSqlDatabase::database(connectionId+"_login");
    db.setDatabaseName("db/login.db");

    if (!db.open())
        return false;

    QSqlQuery query(db);
    if(!query.exec("SELECT COUNT(*) FROM LOGIN WHERE USER = '"+_user+"' AND SITEID != '"+QString::number(_siteID)+"';")) {
        db.close();
        return false;
    }

    query.next();

    if (query.value("COUNT(*)").toInt() == 0) {
        _type = LoginInfo::search_user_error;
    } else {
        _type = LoginInfo::search_user_ok;
    }

    db.close();
    return true;
}