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
#include <QMenu>
#include <QMimeData>


MyTextEdit::MyTextEdit(std::shared_ptr<std::list<RemoteCursor>> remoteCursors, QWidget *parent) : QTextEdit(parent){
    this->remoteCursors = remoteCursors;
    this->installEventFilter(this);
    clipboard = QApplication::clipboard();

    setMouseTracking(true);
    installEventFilter(this);
    toolTipPalette = QToolTip::palette();
    auto font = QFont();
    font.setPointSize(10);
    this->setFont(font);
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
        auto event = static_cast<QKeyEvent*>(ev);
        if(event->matches(QKeySequence::Paste)) {
            this->paste();
            return true;
        }
        return false;
    }

    if(obj == this && ev->type() == QEvent::ToolTip) {
        auto event = dynamic_cast<QHelpEvent *>(ev);
        auto pos = event->pos();
        QTextCursor curs = cursorForPosition(pos);
        int posInText = curs.position();
        QTextCursor tmp = curs;
        tmp.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
        if (!curs.atEnd() && posInText != 0 && tmp.columnNumber() &&
            curs.columnNumber() && document()->characterAt(posInText).unicode() != 8233) {

            emit tipRequest(posInText, event->globalPos());

        }
    }
    return false;
}



void MyTextEdit::contextMenuEvent(QContextMenuEvent *e) {
    auto menu = createStandardContextMenu();
    auto point = e->pos();
    auto curs = cursorForPosition(point);
    int pos = curs.position();
    if( !( (pos >= textCursor().selectionStart() && pos <= textCursor().selectionEnd()) ||
            (pos >= textCursor().selectionEnd() && pos <= textCursor().selectionStart() ) ) ) {
        this->setTextCursor(cursorForPosition(point));
    }

    menu->actions().at(5)->disconnect();
    connect(menu->actions().at(5),&QAction::triggered,this, &MyTextEdit::paste);
    menu->exec(e->globalPos());
    delete menu;
}

void MyTextEdit::paste() {

    QTextCursor curs = this->textCursor();
    if( curs.selectionEnd()==0 || curs.selectionStart()==0 ) {
        auto data = clipboard->mimeData(QClipboard::Clipboard);

        emit isPastingAtFirst();

        curs.removeSelectedText();
        curs.insertHtml(data->html());

        return;
    }
    QTextEdit::paste();

}