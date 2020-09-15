//
// Created by Windows on 13/08/2020.
//

#include <QtGui/QPainter>
#include <iostream>
#include <QPagedPaintDevice>
#include "MyTextEdit.h"


MyTextEdit::MyTextEdit(std::vector<RemoteCursor> *remoteCursors, QWidget *parent) : QTextEdit(parent){
    this->remoteCursors = std::shared_ptr<std::vector<RemoteCursor>>(remoteCursors);

}

void MyTextEdit::paintEvent(QPaintEvent *e) {
    QTextEdit::paintEvent(e);
    QPainter painter(viewport());
    QPen pen;


    for (auto & remoteCursor : *remoteCursors) {
        if(remoteCursor.getSiteId() > 0) {
            pen.setColor(remoteCursor.color);
            pen.setWidth(2);
            painter.setPen(pen);

            const QRect curRect = cursorRect(remoteCursor);
            painter.drawLine(curRect.topLeft(), curRect.bottomLeft());

//            if (remoteCursor.labelTimer->isActive())
//                remoteCursor.labelTimer->stop();

//            remoteCursor.labelName->setParent(this);
//            remoteCursor.labelName->show();
//            remoteCursor.labelName->move(curRect.left() +  70, curRect.top() + 60);
//            remoteCursor.labelTimer->setParent(this);
//            remoteCursor.labelTimer->start(5000);
        }
    }
}

