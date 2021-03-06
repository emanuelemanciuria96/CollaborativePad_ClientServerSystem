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
#include "InfoUsersListWidget.h"
#include <QScrollArea>
#include "UsersList.h"


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow( QWidget* parent = 0);

    enum dock_type{tree,invitelist,uri};
    static QPixmap roundImage(const QPixmap& orig);

private:
    SharedEditor* shEditor; //
    QVector<QDockWidget*> leftDockWidgets; //
    FileSystemTreeView *treeView; //
    FileSystemGridView *gridView; //
    EditorGUI *editor; //
    LoginDialog *loginDialog; //
    QStatusBar* statusBar;
    QToolBar* toolBar;
    QToolBar* gridToolBar;
    QToolBar* richTextBar;
    InfoWidget* infoWidget; //
    InfoWidgetEdit* infoWidgetEdit; //
    QStackedWidget* centralWidget;
    QAction* highlightAction;
    QAction* closeAction;
    QAction* addAction;
    QAction* deleteAction;
    QAction* backAction;
    QAction* inviteAction;
    QAction* treeShowAction;
    QAction* pdfAction;
    QAction* actionAlignLeft;
    QAction* actionAlignCenter;
    QAction* actionAlignRight;
    QAction* actionAlignJustify;
    QAction* uriAction;
    QAction* inviteListAction;
    QAction* undoAction;
    QAction* redoAction;
    QAction* cutAction;
    QAction* copyAction;
    QAction* pasteAction;
    QAction* boldAction;
    QAction* italicAction;
    QAction* underlineAction;
    QComboBox* comboSize;
    QFontComboBox* comboFont;
    QAction* textColorAction;
    QAction* userInfoAction;
    SignInWidget *widgetSignIn; //
    AddUserWidget* addUserWidget; //
    InviteUserWidget* inviteUserWidget; //
    UriWidget* uriWidget; //
    QPixmap bkgnd;
    QDockWidget *dockWidgetUsers; //
    UsersList *usersList; //
    QPalette mainPalette;
    QConicalGradient* gradient;
    QLabel *numUsers;
    QWidget *lastCentral;
    QDockWidget *lastDock;
    InfoUsersListWidget *infoUsersListWidget;
    QWidget *nullWidg;
    QLabel* spinner;
    QWidget* lostConnectionWidget;

    void constructMainWindowMembers();
    void deleteMainWindowMembers();
    void loginSettings();
    void editorSettings();
    void treeFileSystemSettings();
    void gridFileSystemSettings();
    void inviteUserListSetup();
    void signInWidgetSetup();
    void uriWidgetSetup();
    void resizeEvent(QResizeEvent *evt) override;
    void setStyleSheet();
    void setToolBars();
    void setToolBarEditor();
    void setToolBarGrid();
    void setToolBarFolderGrid(QString folder);
    void changeInviteAction(bool state);
    void changeDeleteAction(bool state);
    void showHideLeftDock(dock_type dock);
    void setInviteListIcon(int num=0);
    void setRichTextBar();
    void setUsersList();
    void setGradient();
    void createLostConnWidget();
    void keyPressEvent(QKeyEvent *e) override;
public slots:
    void logout();
    void hideEditor(QString& fileName);
    void setAlignmentActionChecked();
    void setAlignLeftChecked();
    void setAlignCenterChecked();
    void setAlignRightChecked();
    void setAlignJustifyChecked();
    void undoredoActionEnable(bool undo,bool redo){
        undoAction->setEnabled(undo);
        redoAction->setEnabled(redo);
    }
    void clipboardDataChanged(){
#ifndef QT_NO_CLIPBOARD
        if (const QMimeData *md = QApplication::clipboard()->mimeData())
            pasteAction->setEnabled(md->hasText());
#endif
    }
    void loginFinished();
    void startSignIn();
    void backToLogIn();
    void opnFileGrid(QString& fileName);
    void clsFile();
    void openAddUser(const QString& fileName);
    void changeToolbarProfileImage(const QPixmap& image);
    void setNumUsers(int n);
    void hideNumUsers();
    void transparentForMouse();
    void setInfoWidget();
    void setInfoUsersListWidget(const QPixmap& image, const QString& nickname, const QString& name, const QString& email);
    void openInfoEdit(const QPixmap& image, const QString& nickname, const QString& name, const QString& email);
    void colorChanged(const QColor &c);
    void fontChanged(const QFont &f);
    void serverUnavailable();
    void errorArrived(const QString& message);
    void socketError();
    void warningArrived(const QString& message);

signals:
    void sendComboSizeText(const QString& p);
};


#endif //CLIENT_MAINWINDOW_H
