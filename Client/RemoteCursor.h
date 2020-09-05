//
// Created by Windows on 15/04/2020.
//

#ifndef CLIENT_REMOTECURSOR_H
#define CLIENT_REMOTECURSOR_H


#include <QtCore/QtGlobal>
#include <QTextCursor>
#include <QtWidgets/QLabel>
#include "CursorNames.h"
#include <QTimer>
#include <memory>
#include <QtCore/QPointer>
#include "CursorColors.h"

class RemoteCursor : public QTextCursor{
private:
    qint32 _siteId;
    QString generateName() const;
    QString getColor() const;
public:
    QLabel* labelName;
    QPointer<QTimer> labelTimer;
    QColor color;
    static QString getColor(qint32 siteId);
    RemoteCursor(): QTextCursor(){ _siteId = -1;};
    explicit RemoteCursor(qint32 siteId) : _siteId(siteId), QTextCursor() {};
    RemoteCursor(QTextDocument *document, qint32 siteId);
    qint32 getSiteId() const;

    virtual ~RemoteCursor();

};


#endif //CLIENT_REMOTECURSOR_H
