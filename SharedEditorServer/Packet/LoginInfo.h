//
// Created by utente on 17/03/2020.
//

#ifndef SHAREDEDITORSERVER_LOGININFO_H
#define SHAREDEDITORSERVER_LOGININFO_H

#include <QtGlobal>
#include <QtCore/QString>
#include "Payload.h"
#include <fstream>
#include "../json/json.h"

class LoginInfo: public Payload {
private:
    QString _user;
    QString _password;
    qint32 _type;

public:
    LoginInfo(qint32 siteId = -1, qint32 type = -1, const QString user = "", const QString password = "");

    typedef enum Constants
    {
        login_request = 200,
        signup_request = 201,
        login_error = 400,
        login_ok = 100,
    } type_t;

    QString &getUser();
    void setUser(QString user);
    QString &getPassword();
    void setPassword(QString password);
    qint32 getType();
    void setType(type_t type);

    qint32 login();
    LoginInfo loadLoginJson(std::string dir);

};


#endif //SHAREDEDITORSERVER_LOGININFO_H
