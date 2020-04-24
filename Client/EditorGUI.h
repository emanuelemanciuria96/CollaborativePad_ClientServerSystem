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
#include "SharedEditor.h"
#include "RemoteCursor.h"

class EditorGUI: public QMainWindow {
    Q_OBJECT

private:
    QStatusBar* statusBar;
    QTextEdit* textEdit;
    QToolBar* toolBar;
    QString fileName;
    SharedEditor* model;
    bool signalBlocker;
    std::vector<RemoteCursor> remoteCursors;
    QAction* actionSave;

    void setUpGUI();
    void setupFileActions();
    void setupEditActions();
    void setupTextActions();
    void setCurrentFileName(const QString &filename);
    bool load(const QString &f);
    void loadSymbols();
    void updateRemoteCursor(qint32 siteId, int pos);
    void removeCursor(qint32 siteId);
    void fileNew();
    void fileOpen();
    void fileSave();
    void fileSaveAs();

private slots:
    void contentsChange(int pos, int charsRemoved, int charsAdded);

public slots:
    void updateSymbols(qint32 pos, QChar value, const QString& action);

signals:

public:
    EditorGUI(SharedEditor *model, QWidget *parent = nullptr);
    void setModel(SharedEditor *_model);
    void insertText(qint32 pos, QChar value);
    void deleteText(qint32 pos);
};


#endif //MYTEST_EDITORGUI_H
