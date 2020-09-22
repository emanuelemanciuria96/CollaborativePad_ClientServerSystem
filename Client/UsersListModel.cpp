//
// Created by Windows on 18/09/2020.
//

#include "UsersListModel.h"

#include <utility>

UsersListModel::UsersListModel(QObject *parent) : QAbstractListModel(parent) {
    addUser(1, "Piero", QIcon("./images/profile.jpg"));
    addUser(2, "Giacomo", QIcon("./images/profile.jpg"));
    removeUser(2);
}

int UsersListModel::rowCount(const QModelIndex &parent) const {
    return mData.size();
}

QVariant UsersListModel::data(const QModelIndex &index, int role) const {
    if(index.isValid()){
        if(role == Qt::DisplayRole)
            return mData[index.row()].name;
        if(role == Qt::DecorationRole)
            return mData[index.row()].icon;
    }
    return QVariant();
}


void UsersListModel::addUser(qint32 siteId, QString name, QIcon icon) {
    beginInsertRows(QModelIndex(),mData.size(),mData.size());
    mData.append(User(siteId, std::move(name), std::move(icon)));
    endInsertRows();
}

void UsersListModel::removeUser(qint32 siteId) {
    for(auto i = 0; i<mData.size(); i++) {
        if(mData[i].siteId==siteId) {
            beginRemoveRows(QModelIndex(), i, i);
            mData.removeAt(i);
            endRemoveRows();
        }
    }

}


