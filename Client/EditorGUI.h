//
// Created by Windows on 25/03/2020.
//

#ifndef MYTEST_EDITORGUI_H
#define MYTEST_EDITORGUI_H

#include <QGuiApplication>
#include <QtCore/QArgument>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QStatusBar>
#include <QToolBar>
#include <QMenuBar>
#include <QDesktopWidget>
#include <QScreen>
#include <QtCore/QFile>
#include <QTextCodec>
#include <iostream>
#include <QtCore/QTextStream>
#include <QFileInfo>
#include <QTextDocument>
#include <algorithm>
#include "SharedEditor.h"
#include "RemoteCursor.h"
#include <queue>
#include <QTextEdit>
#include "MyTextEdit.h"
#include <QKeyEvent>
#include <QScrollArea>
#include <QAbstractTextDocumentLayout>

class EditorGUI: public QWidget {
    Q_OBJECT

private:
    QString fileName;
    SharedEditor* model;
    bool signalBlocker;
    std::shared_ptr<std::list<RemoteCursor>> remoteCursors;
    std::queue<QChar> insertQueue;
    qint32 siteIdQueue;
    qint32 posQueue;
    qint32 posLastChar;
    QTimer* timer;
    bool selected= false;
    bool myCursorPosUpdateBlocker;
    QTimer* curBlockerTimer;
    uint nUsers = 0;
    std::map<qint32,QString> file_writers;
    QPoint lastToolTipPos;
    bool highlightEditor;
    bool hasSelection = false;
    QTextCharFormat lastFormat;
    Message::action_t lastAction;
    QString *buffer;
    QTimer *bufferTimer;
    qint32 firstPos;
    qint32 tmpPos;

    void setUpGUI();
    void updateRemoteCursors(qint32 mySiteId, int pos);
    RemoteCursor* getRemoteCursor(qint32 siteId);
    void insertText(qint32 pos, const QString& value, qint32 siteId, const QTextCharFormat& format);
    void deleteText(qint32 pos, qint32 siteId,qint32 n);
    static bool checkSiteId(RemoteCursor& rc, qint32 siteId);
    void drawLabel(RemoteCursor *cursor) const;
    void keyPressEvent(QKeyEvent *e) override;
    static QTextCharFormat getHighlightFormat(qint32 siteId);
    void showToolTip(qint32 siteId, QPoint globalPos);

private slots:
    void contentsChange(int pos, int charsRemoved, int charsAdded);
    void flushInsertQueue();
    void setSelected(bool yes){ selected = yes;}
    void handleCursorPosChanged();
    void enableSendCursorPos();
    void checkCharFormat(const QTextCharFormat &f);
    void selectionChanged();
    void flushBuffer();
public slots:
    void updateSymbols(qint32 pos, QString s, qint32 siteId, const QTextCharFormat& format, Message::action_t action);
    void deleteAllText();
    void updateRemoteCursorPos(qint32 pos, qint32 siteId);
    void removeCursor(qint32 siteId);
    void highlight(qint32 pos, qint32 n, qint32 siteId);
    void exportToPdf();
    void setCurrentFileName(QString filename);
    void highlightedTip(int pos,QPoint globalPos);
    void recordUserWriter(qint32 siteId,QString& user,bool connection=false);
    void flushFileWriters();
    void setCharFormat(bool checked);
    void setBold(bool checked) const;
    void setItalic(bool checked) const;
    void setUnderline(bool checked) const;
    void textSize(const QString &p);
    void textFamily(const QString &p);
    void textColor();
    void currentCharFormatChanged(const QTextCharFormat &format);
    void loadHighlights();
    void updateFromOtherEditor(qint32 pos, QChar ch, qint32 siteId, const QTextCharFormat& format, Message::action_t action);

signals:
    void clear();
    void setNumUsers(int n);
    void userQuery(qint32 siteId);
    void updateOther(int, QChar, qint32 siteId,const QTextCharFormat& format, Message::action_t);
    void colorChanged(const QColor &c);
    void fontChanged(const QFont &f);

public:
    MyTextEdit* textEdit;
    EditorGUI(SharedEditor *model, bool highlight,QWidget *parent = nullptr);
    void setModel(SharedEditor *_model);
    void setVerticalScrollValue(int);
    void setHorizontalScrollValue(int);
    int getVerticalScrollValue();
    int getHorizontalScrollValue();
};


#endif //MYTEST_EDITORGUI_H
