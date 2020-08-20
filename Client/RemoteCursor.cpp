//
// Created by Windows on 15/04/2020.
//

#include "RemoteCursor.h"

RemoteCursor::RemoteCursor(QTextDocument *document, qint32 siteId) : _siteId(siteId), QTextCursor(document) {
    color.setNamedColor(getColor());
    labelName = new QLabel();
    labelName->setText(generateName());
    labelName->setStyleSheet("QLabel {background-color: "+ color.name() + "}") ;
    labelTimer = new QTimer();
    labelTimer->setSingleShot(true);
};


qint32 RemoteCursor::getSiteId() const {
    return _siteId;
}

QString RemoteCursor::generateName() {
    auto num = (_siteId*13) % ANIMALS->size();
    return ANIMALS[num];
}

QString RemoteCursor::getColor() {
    auto num = (_siteId*13) % COLORS->size();
    return COLORS[num];
}


