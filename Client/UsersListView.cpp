//
// Created by Windows on 18/09/2020.
//

#include "UsersListView.h"

UsersListView::UsersListView(QWidget  *parent) : QListView(parent){
    auto s = styleSheet();
    s.append("QListView::item{border-radius:8px}");
    setStyleSheet(s);
}


