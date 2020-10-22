//
// Created by Windows on 15/04/2020.
//

#include "RemoteCursor.h"

#include <memory>
#include <iostream>
#include <QtMath>

RemoteCursor::RemoteCursor(QTextDocument *document, qint32 siteId, const QString& username) : _siteId(siteId), QTextCursor(document) {
    color.setNamedColor(getColor());
    labelName = new QLabel();
    labelName->setText(username);
    auto textColor = QColor();
    if(isDarkColor(color))
        textColor.setNamedColor("white");
    else
        textColor.setNamedColor("black");
    labelName->setStyleSheet("QLabel {border-radius:3px; padding:0.5; background-color: "+ color.name() + "; color: " + textColor.name() + "}") ;
    labelTimer = new QTimer();
    labelTimer->setSingleShot(true);
}


qint32 RemoteCursor::getSiteId() const {
    return _siteId;
}

QString RemoteCursor::getColor() const {
    auto num = (_siteId*13) % COLORS->size();
    return COLORS[num];
}

QString RemoteCursor::getColorHex(qint32 siteId) {
    auto num = (siteId*13) % COLORS->size();
    return COLORS[num];
}

RemoteCursor::~RemoteCursor() {
    labelName->deleteLater();
    labelTimer->deleteLater();
}

bool RemoteCursor::isDarkColor(const QColor& c) {
    // brightness  =  sqrt( .241 R^2 + .691 G^2 + .068 B^2 )
    auto brightness = qSqrt(0.241 * c.red()*c.red() + 0.691 * c.green()* c.green() + 0.068 * c.blue()*c.blue());
    return brightness<130;
}
