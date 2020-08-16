//
// Created by Windows on 13/08/2020.
//

#include <QtGui/QPainter>
#include <iostream>
#include "MyTextEdit.h"


MyTextEdit::MyTextEdit(std::vector<RemoteCursor>& remoteCursors, QWidget *parent) : QTextEdit(parent){
    this->remoteCursors = &remoteCursors;
}

void MyTextEdit::paintEvent(QPaintEvent *e) {
    QTextEdit::paintEvent(e);
    QPainter painter(viewport());

//    if (remoteCursors->empty())
//        std::cout << "cursori vuoto" << std::endl;
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    painter.setPen(pen);
    for (auto & remoteCursor : *remoteCursors) {
//        std::cout << remoteCursor.getSiteId() << std::endl;
        const QRect curRect = cursorRect(remoteCursor);
        painter.drawLine(curRect.topLeft(),curRect.bottomLeft());
    }
}

