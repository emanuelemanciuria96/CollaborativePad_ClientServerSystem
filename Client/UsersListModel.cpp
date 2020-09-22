//
// Created by Windows on 18/09/2020.
//

#include "UsersListModel.h"

#include <utility>

UsersListModel::UsersListModel(QObject *parent) : QAbstractListModel(parent) {
//    addUser(1, "Piero", QIcon("./images/profile.jpg"));
//    addUser(2, "Giacomo", QIcon("./images/profile.jpg"));
//    removeUser(2);
}

int UsersListModel::rowCount(const QModelIndex &parent) const {
    return mData.size();
}

QVariant UsersListModel::data(const QModelIndex &index, int role) const {
    if(index.isValid()){
        if(role == Qt::DisplayRole)
            return mData[index.row()].getUsername();
        if(role == Qt::DecorationRole) {
            if (mData[index.row()].getImage().isNull())
                return QIcon("./images/profile.jpg");
            else
                return mData[index.row()].getImage();
        }
        if(role == Qt::BackgroundRole)
            return QColor(RemoteCursor::getColor(mData[index.row()].getSiteId()));

    }
    return QVariant();
}


void UsersListModel::addUser(const UserInfo& user) {
    beginInsertRows(QModelIndex(),mData.size(),mData.size());
    mData.append(user);
    endInsertRows();
}

void UsersListModel::removeUser(const UserInfo& user) {
    for(auto i = 0; i<mData.size(); i++) {
        if(mData[i].getSiteId()==user.getSiteId()) {
            beginRemoveRows(QModelIndex(), i, i);
            mData.removeAt(i);
            endRemoveRows();
        }
    }

}


