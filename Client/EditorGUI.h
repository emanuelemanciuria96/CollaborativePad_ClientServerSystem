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

class EditorGUI: public QMainWindow {
    Q_OBJECT

public:
    explicit EditorGUI(QWidget *parent = nullptr);

private:
    QStatusBar* statusBar;
    QTextEdit* textEdit;
    QToolBar* toolBar;
    QString fileName;
    void setUpGUI();
    void setupFileActions();
    void setupEditActions();
    void setupTextActions();
    void setCurrentFileName(const QString &filename);
    bool load(const QString &f);
};


#endif //MYTEST_EDITORGUI_H
