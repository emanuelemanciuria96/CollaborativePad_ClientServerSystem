//
// Created by utente on 17/03/2020.
//

#ifndef SHAREDEDITORSERVER_LOGININFO_H
#define SHAREDEDITORSERVER_LOGININFO_H

#include <QtGlobal>
#include <QtCore/QString>
#include "Payload.h"
#include <fstream>
#include <QtGui/QPixmap>
#include "../json/json.h"

class LoginInfo: public Payload {
public:
    typedef enum Constants
    {
        not_assigned = -1,
        login_request = 200,
        signup_request = 201,
        update_info = 202,
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
    const QPixmap &getImage() const;
    void setImage(const QPixmap &image);
    const QString &getName() const;
    void setName(const QString &name);

    qint32 login(const QString& connectionId);
    bool updateInfo(const QString& connectionId);

private:
    QString _user;
    QString _password;
    type_t _type;
    QPixmap _image;
    QString _name;
};


#endif //SHAREDEDITORSERVER_LOGININFO_H
