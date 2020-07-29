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
public:
    typedef enum Constants
    {
        not_assigned = -1,
        login_request = 200,
        signup_request = 201,
        login_error = 400,
        login_ok = 100,
    } type_t;

    LoginInfo(qint32 siteId, type_t type = not_assigned, QString user = "", QString password = "");

    QString &getUser();
    void setUser(QString user);
    QString &getPassword();
    void setPassword(QString password);
    type_t getType();
    void setType(type_t type);

    qint32 login(const QString& connectionId);

private:
    QString _user;
    QString _password;
    type_t _type;
};


#endif //SHAREDEDITORSERVER_LOGININFO_H
