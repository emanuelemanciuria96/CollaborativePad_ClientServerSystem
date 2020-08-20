//
// Created by Windows on 13/08/2020.
//

#ifndef CLIENT_MYTEXTEDIT_H
#define CLIENT_MYTEXTEDIT_H


#include <QtWidgets/QTextEdit>
#include "RemoteCursor.h"
#include <memory>

class MyTextEdit : public QTextEdit{
    Q_OBJECT
private:
    std::shared_ptr<std::vector<RemoteCursor>> remoteCursors;
public:
    MyTextEdit(std::vector<RemoteCursor> *remoteCursors, QWidget* parent = 0);
protected:
    void paintEvent(QPaintEvent *e) override;
};


#endif //CLIENT_MYTEXTEDIT_H
