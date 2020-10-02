//
// Created by Windows on 30/09/2020.
//

#ifndef CLIENT_USERSLIST_H
#define CLIENT_USERSLIST_H


#include <QtWidgets/QListWidget>
#include "Packet/UserInfo.h"

class UsersList : public QListWidget{
    Q_OBJECT
    struct UserData {
        QPixmap image;
        QString username;
        QString name;
        QString email;
    };
public:
    UsersList(QWidget* parent);
public slots:
    void removeUser(const UserInfo& user);
    void addUser(const UserInfo& user);
    void openUserInfo(QListWidgetItem* item);
signals:
    void setUserInfo(const QPixmap& image, const QString& nickname, const QString& name, const QString& email);
private:
    QPainterPath roundRect(int width, int height);
    std::map<QListWidgetItem*, struct UserData> map;
};


#endif //CLIENT_USERSLIST_H
