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
#include <QTextBlock>
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
    bool isTextSelected= false;
    bool myCursorPosUpdateBlocker;
    QTimer* curBlockerTimer;
    uint nUsers = 0;
    std::map<qint32,QString> file_writers;
    QPoint lastToolTipPos;
    bool hasSelection = false;
    bool isPastingAtFirst = false;
    static bool isModifying;
    qint32 tmpPos;
    bool highlightIsActive = false;
    QString stylestring;

    void setUpGUI();
    RemoteCursor* getRemoteCursor(qint32 siteId);
    void insertText(qint32 pos, const QString& value, qint32 siteId, const QTextCharFormat& format);
    void deleteText(qint32 pos, qint32 siteId,qint32 n);
    static bool checkSiteId(RemoteCursor& rc, qint32 siteId);
    void drawLabel(RemoteCursor *cursor) const;
    void keyPressEvent(QKeyEvent *e) override;
    static QTextCharFormat getHighlightFormat(qint32 siteId);
    void showToolTip(qint32 siteId, QPoint globalPos);
    void textFormatChange(int pos, int charsModified);

private slots:
    void contentsChange(int pos, int charsRemoved, int charsAdded);
    void flushInsertQueue();
    void setSelected(bool yes){ isTextSelected = yes;}
    void handleCursorPosChanged();
    void enableSendCursorPos();
    void selectionChanged();

public slots:
    void updateSymbols(qint32 pos, const QString& s, qint32 siteId, const QTextCharFormat& format, Message::action_t action);
    void updateAlignment(int pos, Qt::Alignment a);
    void deleteAllText();
    void updateRemoteCursorPos(qint32 pos, qint32 siteId);
    void removeCursor(qint32 siteId);
    void highlight(qint32 pos, qint32 n, qint32 siteId,QTextCursor& cursor);
    void exportToPdf();
    void setCurrentFileName(QString& filename);
    void highlightedTip(int pos,QPoint globalPos);
    void recordUserWriter(qint32 siteId,QString& user,bool connection=false);
    void flushFileWriters();
    void setBold(bool checked);
    void setItalic(bool checked);
    void setUnderline(bool checked);
    void loadHighlights(bool checked);
    void textSize(const QString &p);
    void textFamily(const QString &p);
    void textColor();
    void currentCharFormatChanged(const QTextCharFormat &format);
    void updateLabels();
    void setAbsoluteAlignment(int pos, QFlags<Qt::AlignmentFlag> a,bool selection);

signals:
    void clear();
    void userQuery(qint32 siteId);
    void colorChanged(const QColor &c);
    void fontChanged(const QFont &f);

public:
    MyTextEdit* textEdit;
    EditorGUI(SharedEditor *model, QWidget *parent = nullptr);
    void setModel(SharedEditor *_model);
    bool alignmentCommand=false;


};


#endif //MYTEST_EDITORGUI_H
