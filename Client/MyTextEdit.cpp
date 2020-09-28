//
// Created by Windows on 13/08/2020.
//

#include <QtGui/QPainter>
#include <iostream>
#include <QPagedPaintDevice>
#include <QtGui/QHelpEvent>
#include "MyTextEdit.h"
#include "RemoteCursor.h"
#include <QToolTip>
#include <QMouseEvent>


MyTextEdit::MyTextEdit(std::vector<RemoteCursor> *remoteCursors, QWidget *parent) : QTextEdit(parent){
    this->remoteCursors = std::shared_ptr<std::vector<RemoteCursor>>(remoteCursors);
    this->installEventFilter(this);

    setMouseTracking(true);
    installEventFilter(this);
    toolTipPalette = QToolTip::palette();

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

bool MyTextEdit::eventFilter(QObject *obj, QEvent *ev) {
//    std::cout << "filtro evento del tipo: "<< ev->type() << std::endl;
    if(obj == this && ev->type() == QEvent::ToolTip){
        auto event = dynamic_cast<QHelpEvent*>(ev);
        auto pos = event->pos();
        QTextCursor curs = cursorForPosition(pos);
        int posInText = curs.position();
        QTextCursor tmp = curs;
        tmp.movePosition(QTextCursor::Right,QTextCursor::KeepAnchor);
        if( !curs.atEnd() && posInText!=0 && tmp.columnNumber() &&
            curs.columnNumber() && document()->characterAt(posInText).unicode()!=8233 ){

            emit tipRequest(posInText, event->globalPos());
//            std::cout << "moved in position" << posInText << std::endl;
        }
    }
    else
        QToolTip::setPalette(toolTipPalette);
    return false;
}

void MyTextEdit::showToolTip(qint32 siteId, QPoint globalPos, QString name) {
    auto palette = QPalette();
    auto oldPalette = QToolTip::palette();
    palette.setColor(QPalette::ToolTipBase,RemoteCursor::getColor(siteId));
    QToolTip::setPalette(palette);
    QToolTip::showText(globalPos,name);

}