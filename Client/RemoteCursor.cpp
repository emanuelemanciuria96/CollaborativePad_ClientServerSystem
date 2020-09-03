//
// Created by Windows on 15/04/2020.
//

#include "RemoteCursor.h"

#include <memory>
#include <iostream>

RemoteCursor::RemoteCursor(QTextDocument *document, qint32 siteId) : _siteId(siteId), QTextCursor(document) {
    color.setNamedColor(getColor());
    labelName = new QLabel();
    labelName->setText(generateName());
    labelName->setStyleSheet("QLabel {background-color: "+ color.name() + "}") ;
    labelTimer = new QTimer();
    labelTimer->setSingleShot(true);
}


qint32 RemoteCursor::getSiteId() const {
    return _siteId;
}

QString RemoteCursor::generateName() const {
    auto num = (_siteId*13) % ANIMALS->size();
    return ANIMALS[num];
}

QString RemoteCursor::getColor() const {
    auto num = (_siteId*13) % COLORS->size();
    return COLORS[num];
}

QString RemoteCursor::getColor(qint32 siteId) {
    auto num = (siteId*13) % COLORS->size();
    return COLORS[num];
}

RemoteCursor::~RemoteCursor() {
//    if (labelTimer == nullptr)
//        std::cout << "timer null" << std::endl;
//    else
//        std::cout << "timer not null" << std::endl;
    labelTimer->deleteLater();
}


