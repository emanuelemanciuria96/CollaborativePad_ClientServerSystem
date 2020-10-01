//
// Created by Windows on 30/09/2020.
//

#include "UsersListItem.h"

#include <utility>


UsersListItem::UsersListItem(QString text) : QListWidgetItem(text){
    setName(text);
}

void UsersListItem::setName(QString& name) {
    m_name = name;
}

QString UsersListItem::name() const {
    return m_name;
}