//
// Created by Windows on 18/09/2020.
//

#ifndef CLIENT_USERSLISTMODEL_H
#define CLIENT_USERSLISTMODEL_H

#include <QAbstractListModel>
#include "Packet/UserInfo.h"
#include <QIcon>
#include "RemoteCursor.h"

class UsersListModel : public QAbstractListModel {
    Q_OBJECT
private:
    QList<UserInfo> mData;
public:
    explicit UsersListModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void clear();
public slots:
    void removeUser(const UserInfo& user);
    void addUser(const UserInfo& user);

};


#endif //CLIENT_USERSLISTMODEL_H
