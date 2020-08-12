//
// Created by utente on 06/08/2020.
//

#ifndef CLIENT_MAINWINDOW_H
#define CLIENT_MAINWINDOW_H

#include <QtWidgets>
#include <QGroupBox>
#include "EditorGUI.h"
#include "LoginDialog.h"
#include "FileSystemTreeView.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(SharedEditor* shEditor, QWidget* parent = 0);

private:

    QDockWidget *dockWidgetTree;
    QWidget *widgetLogin;
    QWidget *widgetEditor;
    FileSystemTreeView *treeView;
    EditorGUI *editor;
    LoginDialog *loginDialog;
    QStatusBar* statusBar;
    QToolBar* toolBar;

    void loginSettings();
    void editorSettings(SharedEditor* shEditor);
    void treeFileSystemSettings();

signals:
    void fileSystemRequest();

public slots:
    void loginFinished();

};


#endif //CLIENT_MAINWINDOW_H
