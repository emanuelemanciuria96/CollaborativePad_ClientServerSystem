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

MyTextEdit::MyTextEdit(std::shared_ptr<std::list<RemoteCursor>> remoteCursors,SharedEditor* _model, QWidget *parent) : QTextEdit(parent){
    this->remoteCursors = remoteCursors;
    this->installEventFilter(this);
    this->model = _model;
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
        if(remoteCursor.getSiteId() > 0 && remoteCursor.getSiteId()!= model->getSiteId()) {
            pen.setColor(remoteCursor.color);
            pen.setWidth(2);
            painter.setPen(pen);

            const QRect curRect = cursorRect(remoteCursor);
            painter.drawLine(curRect.topLeft(), curRect.bottomLeft());

        }
    }

    update();
}

bool MyTextEdit::eventFilter(QObject *obj, QEvent *ev){
    if( obj==this && ev->type() == QEvent::KeyPress){
        auto event = static_cast<QKeyEvent*>(ev);

        if(event->matches(QKeySequence::Undo)) {
            emit undo();
            return true;
        }
        if(event->matches(QKeySequence::Redo)) {
            emit redo();
            return true;
        }
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


    menu->actions().at(0)->setIcon(QIcon("./icons/context_undo"));
    menu->actions().at(1)->setIcon(QIcon("./icons/context_redo"));
    menu->actions().at(3)->setIcon(QIcon("./icons/context_cut"));
    menu->actions().at(4)->setIcon(QIcon("./icons/context_copy"));
    menu->actions().at(5)->setIcon(QIcon("./icons/context_paste"));
    menu->actions().at(6)->setIcon(QIcon("./icons/context_eraser"));
    menu->actions().at(8)->setIcon(QIcon("./icons/context_selectall"));
    menu->actions().at(0)->disconnect();
    connect(menu->actions().at(0),&QAction::triggered,[this](){ emit undo(); });
    menu->actions().at(0)->setEnabled(isUndoEnabled);
    menu->actions().at(1)->disconnect();
    connect(menu->actions().at(1),&QAction::triggered,[this](){ emit redo(); });
    menu->actions().at(1)->setEnabled(isRedoEnabled);
    menu->actions().at(5)->disconnect();
    connect(menu->actions().at(5),&QAction::triggered,this, &MyTextEdit::paste);
    menu->exec(e->globalPos());
    delete menu;
}

void MyTextEdit::paste() {

    QTextCursor curs = this->textCursor();
    auto data = clipboard->mimeData(QClipboard::Clipboard);
    if( curs.selectionEnd()==0 || curs.selectionStart()==0 ) {

        emit isPastingAtFirst();
        curs.removeSelectedText();
        curs.insertHtml(data->html());

        return;
    }
    QTextEdit::paste();
}

void MyTextEdit::scrollContentsBy(int dx, int dy) {
    QTextEdit::scrollContentsBy(dx,dy);
    emit updateLabels();
}