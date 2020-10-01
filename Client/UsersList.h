//
// Created by Windows on 30/09/2020.
//

#ifndef CLIENT_USERSLIST_H
#define CLIENT_USERSLIST_H


#include <QtWidgets/QListWidget>
#include "Packet/UserInfo.h"

class UsersList : public QListWidget{
    Q_OBJECT
public:
    UsersList(QWidget* parent);

public slots:
    void removeUser(const UserInfo& user);
    void addUser(const UserInfo& user);
private:
    QPainterPath roundRect(int width, int height);
};


#endif //CLIENT_USERSLIST_H
