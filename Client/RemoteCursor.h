//
// Created by Windows on 15/04/2020.
//

#ifndef CLIENT_REMOTECURSOR_H
#define CLIENT_REMOTECURSOR_H


#include <QtCore/QtGlobal>
#include <QTextCursor>
#include <QtWidgets/QLabel>

class RemoteCursor : public QTextCursor{
    qint32 _siteId;
    int _pos;

public:
    RemoteCursor(qint32 siteId, int pos);
};


#endif //CLIENT_REMOTECURSOR_H
