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
#include "FileSystemGridView.h"
#include "InfoWidget.h"
#include "InfoWidgetEdit.h"
#include "SignInWidget.h"
#include "AddUserWidget.h"
#include "InviteUserWidget.h"
#include "UriWidget.h"
#include "UsersListView.h"
#include "UsersListModel.h"
#include <QScrollArea>
#include "UsersList.h"


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(SharedEditor* shEditor, QWidget* parent = 0);

    enum dock_type{tree,invitelist,uri};

private:
    QVector<QDockWidget*> leftDockWidgets;
    FileSystemTreeView *treeView;
    FileSystemGridView *gridView;
    EditorGUI *editor;
    LoginDialog *loginDialog;
    QStatusBar* statusBar;
    QToolBar* toolBar;
    InfoWidget* infoWidget;
    QStackedWidget* centralWidget;
    QAction* highlightAction;
    QAction* closeAction;
    QAction* addAction;
    QAction* deleteAction;
    QAction* backAction;
    QAction* inviteAction;
    QAction* treeShowAction;
    QAction* pdfAction;
    QAction* uriAction;
    QAction* inviteListAction;
    QAction* undoAction;
    QAction* redoAction;
    QAction* cutAction;
    QAction* copyAction;
    QAction* pasteAction;

    QAction* userInfoAction;
    SignInWidget *widgetSignIn;
    AddUserWidget* addUserWidget;
    InviteUserWidget* inviteUserWidget;
    UriWidget* uriWidget;
    QPixmap bkgnd;
    UsersListView *usersView;
    QDockWidget *dockWidgetUsers;
//    UsersListModel *usersModel;
    UsersList *usersList;
    QPalette mainPalette;
    QConicalGradient* gradient;
    QLabel *numUsers;

    void loginSettings();
    void editorSettings(SharedEditor* shEditor);
    void treeFileSystemSettings();
    void gridFileSystemSettings();
    void inviteUserListSetup();
    void signInWidgetSetup();
    void uriWidgetSetup();
    void resizeEvent(QResizeEvent *evt) override;
    void setStyleSheet();
    void setToolBar();
    void setToolBarEditor();
    void setToolBarGrid();
    void setToolBarFolderGrid(QString folder);
    void changeInviteAction(bool state);
    void changeDeleteAction(bool state);
    void showHideLeftDock(dock_type dock);
    void setInviteListIcon(int num=0);

    void setUsersList();
    void setMainPalette();

public slots:
    void loginFinished();
    void startSignIn();
    void backToLogIn();
    void opnFileGrid(QString fileName);
    void clsFile();
    void openAddUser(const QString& fileName);
    void changeToolbarProfileImage(const QPixmap& image);
    void setNumUsers(int n);
    void hideNumUsers();
    void transparentForMouse();
};


#endif //CLIENT_MAINWINDOW_H