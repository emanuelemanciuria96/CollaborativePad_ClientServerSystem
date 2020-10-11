//
// Created by Windows on 30/09/2020.
//

#include <iostream>
#include <QtGui/QPainter>
#include "UsersList.h"
#include "RemoteCursor.h"

UsersList::UsersList(QWidget *parent) : QListWidget(parent){
    setIconSize(QSize(35,35));
    connect(this, &QListWidget::itemDoubleClicked, this, &UsersList::openUserInfo);
    setStyleSheet("QListWidget::item{margin:5px}");
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
    int size = qMax(orig.width(), orig.height());

    QPixmap rounded = QPixmap(size, size);
    rounded.fill(Qt::transparent);
    QPainterPath path;
    path.addEllipse(rounded.rect());
    QPainter painter(&rounded);
    painter.setClipPath(path);
    painter.fillRect(rounded.rect(), Qt::black);
    int x = qAbs(orig.width() - size) / 2;
    int y = qAbs(orig.height() - size) / 2;
    painter.drawPixmap(x, y, orig.width(), orig.height(), orig);
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
}

void UsersList::removeUser(const UserInfo &user) {
    auto u = findItems(user.getUsername(),Qt::MatchExactly);
//    std::cout << "User disconnected: " << u.constFirst()->text().toStdString() << std::endl;
    map.erase(u.first());
    takeItem(row(u.first()));
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
