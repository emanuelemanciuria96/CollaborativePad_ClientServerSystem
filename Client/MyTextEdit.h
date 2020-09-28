//
// Created by Windows on 13/08/2020.
//

#ifndef CLIENT_MYTEXTEDIT_H
#define CLIENT_MYTEXTEDIT_H


#include <QtWidgets/QTextEdit>
#include "RemoteCursor.h"
#include <memory>
#include <QApplication>

class MyTextEdit : public QTextEdit{
    Q_OBJECT
private:
    std::shared_ptr<std::vector<RemoteCursor>> remoteCursors;
    QClipboard *clipboard;
public:
    MyTextEdit(std::vector<RemoteCursor> *remoteCursors, QWidget* parent = 0);
protected:
    bool eventFilter(QObject *obj, QEvent *evt);
    void paintEvent(QPaintEvent *e) override;

signals:
    void tipRequest(int pos);
    void selectionReplacement(QString& oldText, QString& newText);

};


#endif //CLIENT_MYTEXTEDIT_H
