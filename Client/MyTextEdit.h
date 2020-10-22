//
// Created by Windows on 13/08/2020.
//

#ifndef CLIENT_MYTEXTEDIT_H
#define CLIENT_MYTEXTEDIT_H


#include <QtWidgets/QTextEdit>
#include "RemoteCursor.h"
#include "SharedEditor.h"
#include <memory>
#include <QApplication>
#include <QEvent>
class MyTextEdit : public QTextEdit{
    Q_OBJECT
private:
    std::shared_ptr<std::list<RemoteCursor>> remoteCursors;
    QClipboard *clipboard;
    QPalette toolTipPalette;
    SharedEditor* model;
public:
    MyTextEdit(std::shared_ptr<std::list<RemoteCursor>> remoteCursors,SharedEditor *model, QWidget* parent = 0);
    bool eventFilter(QObject *obj, QEvent *ev) override;

public slots:
    void paste();

protected:
    void paintEvent(QPaintEvent *e) override;
    void contextMenuEvent(QContextMenuEvent *e) override;
    void scrollContentsBy(int dx, int dy) override;
signals:
    void tipRequest(int pos,QPoint globalPos);
    void isPastingAtFirst();
    void updateLabels();
    void undo();
    void redo();
};


#endif //CLIENT_MYTEXTEDIT_H
