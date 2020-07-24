//
// Created by Windows on 15/04/2020.
//

#include "RemoteCursor.h"

RemoteCursor::RemoteCursor(QTextDocument *document, qint32 siteId) : _siteId(siteId), QTextCursor(document) {
    labelName = new QLabel();
    labelCursor = new QLabel();
    labelName->setText(generateName());
    labelCursor->setText("|");
    labelCursor->setStyleSheet("QLabel {color: red}") ;
    labelName->setStyleSheet("QLabel {background-color: #55ff0000}") ;
};


qint32 RemoteCursor::getSiteId() const {
    return _siteId;
}

QString RemoteCursor::generateName() {
    auto num = (_siteId*13) % ANIMALS->size();
    return ANIMALS[num];
}
//
//RemoteCursor &RemoteCursor::operator=(const RemoteCursor& source) {
//    if(this!= &source){
//        delete
//    }
//    return *this;
//}
