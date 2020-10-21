//
// Created by Windows on 30/09/2020.
//

#include <iostream>
#include <QtGui/QPainter>
#include "UsersList.h"
#include "RemoteCursor.h"
#include "MainWindow.h"

UsersList::UsersList(QWidget *parent) : QListWidget(parent){
    setIconSize(QSize(35,35));
    connect(this, &QListWidget::itemDoubleClicked, this, &UsersList::openUserInfo);
//    setStyleSheet("QScrollBar:vertical {background:white; opacity: 0; width:8px; margin: 0px 0px 0px 0px;}"
//                "QScrollBar::handle:vertical {background: #C3C3C3; border:0px solid lightgray; border-radius:4px;}"
//                "QScrollBar::add-line:horizontal {border: 0px solid grey;background: #32CC99;width: 0px;subcontrol-position: right;subcontrol-origin: margin;}"
//                "QScrollBar::sub-line:horizontal {border: 0px solid grey;background: #32CC99;width: 0px;subcontrol-position: right;subcontrol-origin: margin;}"
//                "QScrollBar:horizontal {background:white; opacity: 1; height:8px; margin: 0px 0px 0px 0px;}"
//                "QScrollBar::handle:horizontal {background: black; max-width: 5px; border:1px solid lightgray; border-radius: 4px; width: 8px ;height:8px}");
    setSpacing(2);
}


void UsersList::addUser(const UserInfo &user) {
    auto newItem = new QListWidgetItem(user.getUsername());
    newItem->setFlags(Qt::ItemIsEnabled);
    newItem->setSizeHint(QSize(134,40));
    auto orig = QPixmap();
    if(user.getImage().isNull())
        orig = QPixmap("./images/profile.jpg");
    else
        orig = QPixmap(user.getImage());

    auto rounded = MainWindow::roundImage(orig);
    newItem->setIcon(QIcon(rounded));

    auto backColor = RemoteCursor::getColorHex(user.getSiteId());
    QPixmap backgrnd = QPixmap(134,40);
    backgrnd.fill(Qt::transparent);
    QPainter backPainter(&backgrnd);
    backPainter.setRenderHint(QPainter::Antialiasing);
    backPainter.setClipPath(roundRect(134,40),Qt::ReplaceClip);
    backPainter.fillRect(backgrnd.rect(), backColor);
    backPainter.drawPixmap(0,0,backgrnd.width(), backgrnd.height(),backgrnd);
    newItem->setBackground(backgrnd);

    if(RemoteCursor::isDarkColor(backColor))
        newItem->setForeground(QColor("white"));
    else
        newItem->setForeground(QColor("black"));

    addItem(newItem);

    struct UserData data;
    data.image = user.getImage();
    data.username = user.getUsername();
    data.name = user.getName();
    data.email = user.getEmail();
    map.insert(std::make_pair(newItem, data));
    emit setNumUsers(this->count());
}

void UsersList::removeUser(const UserInfo &user) {
    auto u = findItems(user.getUsername(),Qt::MatchExactly);
//    std::cout << "User disconnected: " << u.constFirst()->text().toStdString() << std::endl;
    map.erase(u.first());
    takeItem(row(u.first()));
    emit setNumUsers(this->count());
}

QPainterPath UsersList::roundRect(int width, int height) {
    QPainterPath roundRectPath;

    roundRectPath.moveTo(height/2, 0.0);
    roundRectPath.arcTo(0.0, 0.0, height, height, 90.0, 180.0);
    roundRectPath.lineTo(width-(height/2), height);
    roundRectPath.arcTo(width-height, 0.0, height, height, 270.0, 180.0);
    roundRectPath.closeSubpath();
    return roundRectPath;
}

void UsersList::openUserInfo(QListWidgetItem *item) {
    auto user = map[item];
    emit setUserInfo(user.image, user.username, user.name, user.email);
}
