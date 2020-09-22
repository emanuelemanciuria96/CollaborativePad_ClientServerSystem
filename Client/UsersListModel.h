//
// Created by Windows on 18/09/2020.
//

#ifndef CLIENT_USERSLISTMODEL_H
#define CLIENT_USERSLISTMODEL_H

#include <QAbstractListModel>
#include "User.h"
#include <QIcon>

class UsersListModel : public QAbstractListModel {
    Q_OBJECT
private:
    QList< User> mData;
public:
    explicit UsersListModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
public slots:
    void removeUser(qint32 siteId);
    void addUser(qint32 siteId, QString name, QIcon icon);
};


#endif //CLIENT_USERSLISTMODEL_H
