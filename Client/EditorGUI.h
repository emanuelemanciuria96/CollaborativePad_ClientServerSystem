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

class EditorGUI: public QMainWindow {
    Q_OBJECT

private:
    QStatusBar* statusBar;
    QTextEdit* textEdit;
    QToolBar* toolBar;
    QString fileName;
    SharedEditor* model;
    bool signalBlocker;

    void setUpGUI();
    void setupFileActions();
    void setupEditActions();
    void setupTextActions();
    void setCurrentFileName(const QString &filename);
    bool load(const QString &f);
    void loadSymbols();


private slots:
    void contentsChange(int pos, int charsRemoved, int charsAdded);

public slots:
    void updateSymbols(qint32 pos, QChar value, const QString& action);

signals:

public:
    EditorGUI(SharedEditor *model, QWidget *parent = nullptr);
    void setModel(SharedEditor *_model);
    void insertText(qint32 pos, QString value);
    void deleteText(qint32 pos,QString value="a");
};


#endif //MYTEST_EDITORGUI_H
