//
// Created by utente on 18/09/2020.
//

#ifndef SHAREDEDITORSERVER_USERINFO_H
#define SHAREDEDITORSERVER_USERINFO_H

#include <QtGui/QPixmap>
#include "Payload.h"

class UserInfo: public Payload  {
public:
    typedef enum _type{
        conn_broad,
        conn_ack,
        disconnect,
        user_reqest,
    }info_t;

    UserInfo(qint32 siteId, info_t type, QString& user_name):
        Payload(siteId),_type(type),_username(user_name){}
    void setType(info_t type){ _type = type; }
    info_t getType(){ return _type; }
    QString getUsername(){ return _username; }
    QPixmap getImage(){ return _image; }
    bool obtainImage(QString& connectionId);
    bool obtainUser(QString& connectionId);

private:

    info_t _type;
    QString _username;
    QPixmap _image;

};


#endif //SHAREDEDITORSERVER_USERINFO_H
