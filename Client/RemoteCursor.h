//
// Created by Windows on 15/04/2020.
//

#ifndef CLIENT_REMOTECURSOR_H
#define CLIENT_REMOTECURSOR_H


#include <QtCore/QtGlobal>
#include <QTextCursor>
#include <QtWidgets/QLabel>
#include "CursorNames.h"

class RemoteCursor : public QTextCursor{
private:
    qint32 _siteId;
    QString generateName();
public:
    QLabel* labelName;
    QLabel* labelCursor;

    RemoteCursor(): QTextCursor(){ _siteId = -1;};
    explicit RemoteCursor(qint32 siteId) : _siteId(siteId), QTextCursor() {};
    RemoteCursor(QTextDocument *document, qint32 siteId);
//    RemoteCursor& operator=(const RemoteCursor& rc);
    qint32 getSiteId() const;
};


#endif //CLIENT_REMOTECURSOR_H
