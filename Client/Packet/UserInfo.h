//
// Created by utente on 18/09/2020.
//

#ifndef CLIENT_USERINFO_H
#define CLIENT_USERINFO_H

#include <QtGui/QPixmap>
#include "Payload.h"
#include <QIcon>

class UserInfo: public Payload  {
public:
    typedef enum _type{
        conn_broad,
        conn_ack,
        disconnect,
        user_request,
    }info_t;

    UserInfo(qint32 siteId, info_t type, QString& user_name, QPixmap&  image, QString& name, QString& email):
            Payload(siteId),_type(type),_username(user_name),_image(image), _name(name), _email(email){};
    UserInfo(qint32 siteId, info_t type, QString& user_name):
            Payload(siteId),_type(type),_username(user_name){};
    UserInfo(UserInfo&& user) noexcept : _type(user._type),_username(std::move(user._username)),
        _image(user._image), _name(user._name), _email(user._email),Payload(user._siteID){};
    UserInfo(const UserInfo& user) = default;
    UserInfo& operator=(const UserInfo& user){
        if(this!=&user){
            _siteID = user._siteID;
            _username = user._username;
            _type = user._type;
            _image = user._image;
            _name = user._name;
            _email = user._email;
        }
        return *this;
    }

    void setType(info_t type){ _type = type; }
    info_t getType(){ return _type; }
    QString getUsername() const{ return _username; }
    QPixmap getImage() const { return _image; }
    const QString &getName() const { return _name; }
    const QString &getEmail() const { return _email; }

private:
    info_t _type;
    QString _username;
    QPixmap _image;
    QString _name;
    QString _email;
};


#endif //CLIENT_USERINFO_H
