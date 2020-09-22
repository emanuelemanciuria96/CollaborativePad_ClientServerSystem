//
// Created by Windows on 18/09/2020.
//

#ifndef CLIENT_USER_H
#define CLIENT_USER_H

#include <QtCore/QtGlobal>
#include <QtGui/QIcon>
#include <utility>

class User {
public:
    qint32 siteId;
    QString name;
    QIcon icon;
    User() : siteId(-1), name(QString()), icon("./images/profile.jpg"){};
    User(User&& user)   noexcept : siteId(user.siteId), name(std::move(user.name)), icon(std::move(user.icon)) {};
    User(const User& user) = default;
    User& operator=(const User& user){
        if(this!=&user){
            siteId = user.siteId;
            name = user.siteId;
            icon = user.icon;
        }
        return *this;
    };
    User(qint32 siteId, QString  name, QIcon icon) : siteId(siteId), name(std::move(name)), icon(std::move(icon)){};
};


#endif //CLIENT_USER_H
