//
// Created by Windows on 25/03/2020.
//

#ifndef MYTEST_EDITORGUI_H
#define MYTEST_EDITORGUI_H

#include <QGuiApplication>
#include <QtCore/QArgument>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTextEdit>
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

class EditorGUI: public QWidget {
    Q_OBJECT

private:
    QTextEdit* textEdit;
    QString fileName;
    SharedEditor* model;
    bool signalBlocker;
    std::vector<RemoteCursor> remoteCursors;
    QAction* actionSave;
    std::queue<QChar> insertQueue;
    qint32 siteIdQueue;
    qint32 posQueue;
    qint32 posLastChar;
    QTimer* timer;
    bool selected= false;

    void setUpGUI();
   // void setupFileActions();
    void setupEditActions();
    void setupTextActions();
    void setCurrentFileName(const QString &filename);
    bool load(const QString &f);
    void loadSymbols();
    void updateRemoteCursors(qint32 siteId, int pos, Message::action_t action);
    RemoteCursor* getRemoteCursor(qint32 siteId);
    void removeCursor(qint32 siteId);
    void fileNew();
    void fileOpen();
    void fileSave();
    void fileSaveAs();
    void insertText(qint32 pos, const QString& value, qint32 siteId);
    void deleteText(qint32 pos, qint32 siteId,qint32 n);
    static bool checkSiteId(RemoteCursor& rc, qint32 siteId);
    void drawCursor(RemoteCursor *cursor);

private slots:
    void contentsChange(int pos, int charsRemoved, int charsAdded);
    void flushInsertQueue();
    void setSelected(bool yes){ selected = yes;}

public slots:
    void updateSymbols(qint32 pos, QString s, qint32 siteId, Message::action_t action);
    void deleteAllText();

signals:
    void clear();

public:
    EditorGUI(SharedEditor *model, QWidget *parent = nullptr);
    void setModel(SharedEditor *_model);

};


#endif //MYTEST_EDITORGUI_H
