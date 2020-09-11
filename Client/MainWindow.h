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
#include "AddUserWidget.h"
#include "InviteUserWidget.h"
#include "UriWidget.h"

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
    QAction* treeShowAction;
    SignInWidget *widgetSignIn;
    AddUserWidget* addUserWidget;
    InviteUserWidget* inviteUserWidget;
    UriWidget* uriWidget;
    QPixmap bkgnd;

    void loginSettings();
    void editorSettings(SharedEditor* shEditor);
    void treeFileSystemSettings();
    void infoWidgetsSettings();
    void highlightActionSetup();
    void signInWidgetSetup();
    void resizeEvent(QResizeEvent *evt) override;
    void setStyleSheet();
    void createMenus();

private:
    void resizeEvent(QResizeEvent * evt)  override {
        QMainWindow::resizeEvent(evt);
        dockWidgetTree->setMaximumWidth(this->size().width() / 4);
        dockWidgetTree->setMinimumWidth(this->size().width() / 4);
    }

signals:

public slots:
    void loginFinished();
    void startSignIn();
    void backToLogIn();
    void openAddUser(const QString& fileName);
    void showHideTreeDock(bool checked=false){
        if(dockWidgetTree->isHidden())
            dockWidgetTree->show();
        else dockWidgetTree->hide();
    }
};


#endif //CLIENT_MAINWINDOW_H
