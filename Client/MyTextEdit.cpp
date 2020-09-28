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
#include <QtGui/QClipboard>


MyTextEdit::MyTextEdit(std::vector<RemoteCursor> *remoteCursors, QWidget *parent) : QTextEdit(parent){
    this->remoteCursors = std::shared_ptr<std::vector<RemoteCursor>>(remoteCursors);
    this->installEventFilter(this);
    clipboard = QApplication::clipboard();

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

bool MyTextEdit::eventFilter(QObject *obj, QEvent *ev){

    if( obj==this && ev->type() == QEvent::KeyPress){
        auto event = dynamic_cast<QKeyEvent*>(ev);
        QTextCursor curs = this->textCursor();
        if( (curs.selectionEnd()==0 || curs.selectionStart()==0) && event->matches(QKeySequence::Paste)) {
            curs.removeSelectedText();
            curs.insertText(clipboard->text(QClipboard::Clipboard));
            return true;
        }
        return false;
    }

    if( obj == this && ev->type() == QEvent::ToolTip ){
        auto event = dynamic_cast<QHelpEvent*>(ev);
        auto pos = event->pos();
        QTextCursor curs = cursorForPosition(pos);
        int posInText = curs.position();
        QTextCursor tmp = curs;
        tmp.movePosition(QTextCursor::Right,QTextCursor::KeepAnchor);
        if( !curs.atEnd() && posInText!=0 && tmp.columnNumber() &&
            curs.columnNumber() && document()->characterAt(posInText).unicode()!=8233 ){

            emit tipRequest(posInText, event->globalPos());
            std::cout << "moved in position" << posInText << std::endl;
        }
    }
    else
        QToolTip::setPalette(toolTipPalette);
    return false;
}

