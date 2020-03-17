//
// Created by utente on 17/03/2020.
//

#ifndef SHAREDEDITORSERVER_LOGININFO_H
#define SHAREDEDITORSERVER_LOGININFO_H

#include <QtGlobal>
#include <QtCore/QString>
#include "Payload.h"

class LoginInfo: public Payload {
private:
    QString _user;
    QString _password;
public:
    LoginInfo(qint32 siteId):Payload(siteId){}
    void setUser(QString user){ _user = user; }
    void setPassword(QString password){ _password = password; }
};


#endif //SHAREDEDITORSERVER_LOGININFO_H
