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

void LoginInfo::setType(type_t type) {
    _type = type;
}

qint32 LoginInfo::login() {

    LoginInfo logData = loadLoginJson(_user.toStdString()+".json");
    if(_user == logData.getUser() && _password == logData.getPassword()) {
        _type = LoginInfo::login_ok;
        _siteID = 5;
        _user = "";
        _password = "";
        return 5;
    } else {
        _type = LoginInfo::login_error;
        _siteID = -1;
        _user = "";
        _password = "";
        return -1;
    }
}

LoginInfo LoginInfo::loadLoginJson(std::string dir){
    std::ifstream file_input(dir);
    Json::Reader reader;
    Json::Value root;
    reader.parse(file_input, root);

    QString user = QString::fromStdString(root["user"].asString());
    QString password = QString::fromStdString(root["password"].asString());
    LoginInfo data(-1, -1, std::move(user), std::move(password));

    return data;
}