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
#include "InfoWidget.h"
#include "InfoWidgetEdit.h"
#include "SignInWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(SharedEditor* shEditor, QWidget* parent = 0);

private:
    QDockWidget *dockWidgetTree;
    QWidget *widgetLogin;
    QWidget *widgetEditor;
    QWidget *widgetInfoEditC;
    FileSystemTreeView *treeView;
    EditorGUI *editor;
    LoginDialog *loginDialog;
    QStatusBar* statusBar;
    QToolBar* toolBar;
    InfoWidget* infoWidget;
    InfoWidgetEdit* infoWidgetEdit;
    QStackedWidget* centralWidget;
    QAction* highlightAction;
    SignInWidget *widgetSignIn;

    void loginSettings();
    void editorSettings(SharedEditor* shEditor);
    void treeFileSystemSettings();
    void infoWidgetsSettings();
    void highlightActionSetup();
    void signInWidgetSetup();

 signals:
    void fileSystemRequest();

public slots:
    void loginFinished();
    void startSignIn();
    void backToLogIn();
};


#endif //CLIENT_MAINWINDOW_H
