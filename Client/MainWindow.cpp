//
// Created by utente on 06/08/2020.
//

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QDockWidget>
#include "MainWindow.h"


MainWindow::MainWindow(SharedEditor* shEditor, QWidget *parent) : QMainWindow(parent) {
    QApplication::setStyle(QStyleFactory::create("Fusion"));
//    for(auto k : QStyleFactory::keys()){
//        std::cout << k.toStdString() << std::endl;
//    }
    bkgnd = QPixmap("./textures/texture_clouds_background.png");
    setStyleSheet();
    setMainPalette();
    setWindowTitle("Shared Editor");

    //statusBar initialize
    statusBar = new QStatusBar(this);
    numUsers = new QLabel(statusBar);
    numUsers->setText("User connected: 0");
    statusBar->addPermanentWidget(numUsers);
    numUsers->hide();
    statusBar->showMessage ("");
    statusBar->setPalette(mainPalette);
//    statusBar->setStyleSheet(statusBar->styleSheet().append("background-color:#3F51B5"));

    toolBar = new QToolBar("Toolbar",this);
    centralWidget = new QStackedWidget(this);

    //    aggiungo gli elementi alla finestra
    this->setStatusBar(statusBar);
    this->addToolBar(toolBar);
    toolBar->setMovable(false);
    toolBar->setMinimumHeight(45);
    toolBar->setIconSize(QSize(45, 45));
    toolBar->hide();
    setCentralWidget(centralWidget);
    // tree file system view creation
    treeFileSystemSettings();
    // grid file system view creation
    gridFileSystemSettings();
    // login creation
    loginSettings();
    // editor creation
    editorSettings(shEditor);

    signInWidgetSetup();
    setUsersList();

    setToolBar();
    setToolBarGrid();

    connect(loginDialog, &LoginDialog::acceptLogin, shEditor, &SharedEditor::loginSlot);
    connect(treeView, &FileSystemTreeView::opnFileRequest,shEditor , &SharedEditor::requireFile);
    connect(treeView, &FileSystemTreeView::renFileRequest,shEditor , &SharedEditor::requireFileRename);
    connect(treeView, &FileSystemTreeView::newFileAdded,shEditor , &SharedEditor::requireFileAdd);
    connect(treeView, &FileSystemTreeView::rmvFileRequest,shEditor , &SharedEditor::requireFileDelete);
    connect(treeView, &FileSystemTreeView::newFileUpdateGrid, gridView, &FileSystemGridView::constructFromPaths);
    connect(treeView, &FileSystemTreeView::renFileRequest,gridView , &FileSystemGridView::remoteRenameFile);
    connect(treeView, &FileSystemTreeView::rmvFileRequest,gridView , &FileSystemGridView::remoteDeleteFile);
    connect(gridView, &FileSystemGridView::rmvFileRequest,shEditor , &SharedEditor::requireFileDelete);
    connect(gridView, &FileSystemGridView::opnFileRequest,this, &MainWindow::opnFileGrid);
    connect(gridView, &FileSystemGridView::opnFileRequest,shEditor , &SharedEditor::requireFile);
    connect(gridView, &FileSystemGridView::openFolder,this, &MainWindow::setToolBarFolderGrid);
    connect(gridView, &FileSystemGridView::back,this, &MainWindow::setToolBarGrid);
    connect(gridView, &FileSystemGridView::canInvite,this, &MainWindow::changeInviteAction);
    connect(gridView, &FileSystemGridView::renFileRequest,shEditor , &SharedEditor::requireFileRename);
    connect(gridView, &FileSystemGridView::renFileRequest,treeView , &FileSystemTreeView::editFileName);
    connect(gridView, &FileSystemGridView::newFileAdded,shEditor , &SharedEditor::requireFileAdd);
    connect(shEditor, &SharedEditor::fileNameEdited, treeView, &FileSystemTreeView::editFileName);
    connect(shEditor, &SharedEditor::fileDeletion, treeView, &FileSystemTreeView::remoteFileDeletion);
    connect(shEditor, &SharedEditor::loginAchieved, this, &MainWindow::loginFinished);
    connect(shEditor, &SharedEditor::loginError, loginDialog, &LoginDialog::slotLoginError);
    connect(shEditor, &SharedEditor::symbolsChanged, editor, &EditorGUI::updateSymbols);
    connect(shEditor, &SharedEditor::remoteCursorPosChanged, editor, &EditorGUI::updateRemoteCursorPos);
    connect(shEditor, &SharedEditor::removeCursor, editor, &EditorGUI::removeCursor);
    connect(shEditor, &SharedEditor::deleteAllText, editor, &EditorGUI::deleteAllText);
    connect(shEditor, &SharedEditor::filePathsArrived, treeView, &FileSystemTreeView::constructFromPaths);
    connect(shEditor, &SharedEditor::filePathsArrived, gridView, &FileSystemGridView::constructFromPaths);
    connect(gridView, &FileSystemGridView::newFileUpdateTree, treeView, &FileSystemTreeView::constructFromPaths);
    connect(shEditor, &SharedEditor::userInfoArrived, infoWidget, &InfoWidget::loadData);
    connect(infoWidget, &InfoWidget::sendUpdatedInfo, shEditor, &SharedEditor::sendUpdatedInfo);
    connect(loginDialog, &LoginDialog::signIn, this, &MainWindow::startSignIn);
    connect(widgetSignIn, &SignInWidget::backToLogIn, this, &MainWindow::backToLogIn);
    connect(highlightAction, &QAction::triggered, shEditor, &SharedEditor::highlightSymbols);
    connect(closeAction, &QAction::triggered, this, &MainWindow::clsFile);
    connect(shEditor, &SharedEditor::returnToGrid, this, &MainWindow::clsFile);
    connect(closeAction, &QAction::triggered, shEditor, &SharedEditor::requireFileClose);
    connect(pdfAction, &QAction::triggered, editor, &EditorGUI::exportToPdf);
    connect(addAction, &QAction::triggered, gridView, &FileSystemGridView::addFile);
    connect(backAction, &QAction::triggered, gridView, &FileSystemGridView::reloadBack);
    connect(shEditor, &SharedEditor::highlight, editor, &EditorGUI::highlight);
    connect(widgetSignIn, &SignInWidget::registerRequest, shEditor, &SharedEditor::sendRegisterRequest);
    connect(addUserWidget, &AddUserWidget::searchUser, shEditor, &SharedEditor::searchUser);
    connect(shEditor, &SharedEditor::searchUserResult, addUserWidget, &AddUserWidget::searchUserResult);
    connect(shEditor, &SharedEditor::inviteResultArrived, addUserWidget, &AddUserWidget::inviteResultArrived);
    connect(addUserWidget, &AddUserWidget::setStatusBarText, statusBar, &QStatusBar::showMessage);
    connect(addUserWidget, &AddUserWidget::submitInvite, shEditor, &SharedEditor::submitInvite);
    connect(treeView, &FileSystemTreeView::inviteRequest, this, &MainWindow::openAddUser);
    connect(inviteAction, &QAction::triggered, gridView, &FileSystemGridView::invite);
    connect(gridView, &FileSystemGridView::inviteRequest, this, &MainWindow::openAddUser);
    connect(shEditor, &SharedEditor::inviteListArrived, inviteUserWidget, &InviteUserWidget::inviteListArrived);
    connect(inviteUserWidget, &InviteUserWidget::sendInviteAnswer, shEditor, &SharedEditor::sendInviteAnswer);
    connect(shEditor, &SharedEditor::fileNameEdited, inviteUserWidget, &InviteUserWidget::editFileName);
    connect(shEditor, &SharedEditor::fileNameEdited, addUserWidget, &AddUserWidget::editFileName);
    connect(treeView, &FileSystemTreeView::fileNameEdited, addUserWidget, &AddUserWidget::editFileName);
    connect(shEditor, &SharedEditor::fileDeletion, inviteUserWidget, &InviteUserWidget::processFileDeleted);
    connect(treeView, &FileSystemTreeView::rmvFileRequest, addUserWidget, &AddUserWidget::processFileDeleted);
    connect(gridView, &FileSystemGridView::rmvFileRequest, addUserWidget, &AddUserWidget::processFileDeleted);
    connect(gridView, &FileSystemGridView::rmvFileRequest, treeView, &FileSystemTreeView::remoteFileDeletion);
    connect(treeShowAction, &QAction::triggered,[this](bool checked=false){
        if(dockWidgetTree->isHidden()) {
            dockWidgetTree->show();
            treeShowAction->setToolTip("Hide tree");
        }else {
            dockWidgetTree->hide();
            treeShowAction->setToolTip("Show tree");
        }
    });
    connect(uriWidget, &UriWidget::submitUri, shEditor, &SharedEditor::submitUri);
    connect(shEditor, &SharedEditor::uriResultArrived, uriWidget, &UriWidget::uriResultArrived);
    connect(uriWidget, &UriWidget::setStatusBarText, statusBar, &QStatusBar::showMessage);
    connect(shEditor, &SharedEditor::fsNameArrived, addUserWidget, &AddUserWidget::fsNameArrived);
    connect(addUserWidget, &AddUserWidget::searchFsName, shEditor, &SharedEditor::searchFsName);
    connect(treeView, &FileSystemTreeView::opnFileRequest, editor, &EditorGUI::setCurrentFileName);
    connect(gridView, &FileSystemGridView::opnFileRequest, editor, &EditorGUI::setCurrentFileName);
    connect(treeView, &FileSystemTreeView::opnFileRequest, gridView, &FileSystemGridView::selectFile);
    connect(uriAction, &QAction::triggered, uriWidget, &QWidget::show);
    connect(inviteListAction, &QAction::triggered, inviteUserWidget, &QWidget::show);
    connect(userInfoAction, &QAction::triggered, infoWidget, &QWidget::show);
    connect(infoWidget, &InfoWidget::imageChanged, this, &MainWindow::changeToolbarProfileImage);
    connect(editor, &EditorGUI::setNumUsers, this, &MainWindow::setNumUsers);
    connect(shEditor, &SharedEditor::setNumUsers, this, &MainWindow::setNumUsers);
    connect(shEditor, &SharedEditor::hideNumUsers, this, &MainWindow::hideNumUsers);
    connect(shEditor, &SharedEditor::addUser, usersModel, &UsersListModel::addUser);
    connect(shEditor, &SharedEditor::removeUser, usersModel, &UsersListModel::removeUser);

    //    imposto la grandezza della finestra
    auto size = QGuiApplication::primaryScreen()->size();
    this->resize(size.width()*0.7,size.height()*0.7);

    setPalette(mainPalette);
    centralWidget->addWidget(loginDialog);
    centralWidget->addWidget(editor);
    centralWidget->addWidget(widgetSignIn);
    centralWidget->addWidget(gridView);

}

void MainWindow::transparentForMouse(bool var) {
    toolBar->setAttribute(Qt::WA_TransparentForMouseEvents, var);
    gridView->setAttribute(Qt::WA_TransparentForMouseEvents, var);
    treeView->setAttribute(Qt::WA_TransparentForMouseEvents, var);
}

void MainWindow::loginFinished() {
    centralWidget->setCurrentWidget(gridView);
    toolBar->show();
    gridView->show();
}

void MainWindow::opnFileGrid(QString fileName) {
    setToolBarEditor();
    centralWidget->setCurrentWidget(editor);
    dockWidgetUsers->show();
    auto palette = this->palette();
    palette.setColor(QPalette::Window,QColor("lightgray"));
    palette.setColor(QPalette::Base,QColor("white"));
    setPalette(palette);
}

void MainWindow::changeInviteAction(bool state){
    inviteAction->setDisabled(!state);
    if(state){
        inviteAction->setToolTip("Invite user");
    }else{
        inviteAction->setToolTip("");
    }
}
void MainWindow::clsFile() {
    centralWidget->setCurrentWidget(gridView);
    dockWidgetTree->hide();
    if(gridView->getState()==gridView->getMainFolder()){
        setToolBarGrid();
        inviteAction->setDisabled(false);
    }else{
        setToolBarFolderGrid(gridView->getState());
    }
    gridView->show();
    if(highlightAction->isChecked()){
        highlightAction->trigger();
        highlightAction->setChecked(false);
    }
}
void MainWindow::loginSettings() {
    loginDialog = new LoginDialog(this);
    loginDialog->setPalette(mainPalette);
}


void MainWindow::treeFileSystemSettings() {
    dockWidgetTree = new QDockWidget(tr("files"),this);
    dockWidgetTree->setAllowedAreas(Qt::LeftDockWidgetArea );
    dockWidgetTree->setFeatures(QDockWidget::DockWidgetClosable);
    dockWidgetTree->setMouseTracking(true);

    auto voidWidget = new QWidget();
    dockWidgetTree->setTitleBarWidget(voidWidget);

    treeView = new FileSystemTreeView(dockWidgetTree);
    dockWidgetTree->setWidget(treeView);

    this->addDockWidget(Qt::LeftDockWidgetArea,dockWidgetTree);
    dockWidgetTree->hide();
    dockWidgetTree->setPalette(mainPalette);
}

void MainWindow::gridFileSystemSettings() {
    gridView = new FileSystemGridView();
    gridView->setPalette(mainPalette);
}

void MainWindow::setToolBar() {
    //EditorToolbar
    treeShowAction = new QAction();
    treeShowAction->setIcon(QIcon("./icons/left_tree_menu.png"));
    treeShowAction->setVisible(false);
    treeShowAction->setToolTip("Show tree");
    toolBar->addAction(treeShowAction);

    highlightAction=new QAction();
    highlightAction->setCheckable(true);
    highlightAction->setShortcut(QKeySequence::Replace); //equivale a Ctrl+H
    highlightAction->setIcon(QIcon("./icons/highlight.png"));
    highlightAction->setToolTip("Highlight the text entered by different users");
    highlightAction->setVisible(false);
    toolBar->addAction(highlightAction);

    closeAction = new QAction();
    closeAction->setIcon(QIcon("./icons/close.png"));
    closeAction->setVisible(false);
    closeAction->setToolTip("Close file");
    toolBar->addAction(closeAction);

    pdfAction = new QAction();
    pdfAction->setIcon(QIcon("./icons/pdf.png"));
    pdfAction->setVisible(false);
    pdfAction->setToolTip("Save as pdf");
    toolBar->addAction(pdfAction);

    //GridToolbar
    addAction = new QAction();
    addAction->setIcon(QIcon("./icons/grid_add_icon.png"));
    addAction->setVisible(false);
    addAction->setToolTip("New file");
    toolBar->addAction(addAction);

    backAction = new QAction();
    backAction->setIcon(QIcon("./icons/grid_back_icon.png"));
    backAction->setVisible(false);
    backAction->setToolTip("Back");
    toolBar->addAction(backAction);

    inviteAction = new QAction();
    inviteAction->setIcon(QIcon("./icons/grid_invite_icon.png"));
    inviteAction->setVisible(false);
    toolBar->addAction(inviteAction);

    //entrambe
    uriAction = new QAction();
    uriAction->setIcon(QIcon("./icons/uri_icon.png"));
    uriAction->setVisible(true);
    uriAction->setToolTip("Add a file inserting a URI");
    toolBar->addAction(uriAction);

    inviteListAction = new QAction();
    inviteListAction->setIcon(QIcon("./icons/invite_list_icon.png"));
    inviteListAction->setVisible(true);
    inviteListAction->setToolTip("Show invites list");
    toolBar->addAction(inviteListAction);

    userInfoAction = new QAction();
    const QPixmap orig = QPixmap("./images/profile.jpg");
    int size = qMax(orig.width(), orig.height());
    QPixmap rounded = QPixmap(size, size);
    rounded.fill(Qt::transparent);
    QPainterPath path;
    path.addEllipse(rounded.rect());
    QPainter painter(&rounded);
    painter.setClipPath(path);
    painter.fillRect(rounded.rect(), Qt::black);
    int x = qAbs(orig.width() - size) / 2;
    int y = qAbs(orig.height() - size) / 2;
    painter.drawPixmap(x, y, orig.width(), orig.height(), orig);
    userInfoAction->setIcon(QIcon(rounded));
    userInfoAction->setVisible(true);
    userInfoAction->setToolTip("Show or edit user's info");
    auto *spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacerWidget->setVisible(true);
    toolBar->addWidget(spacerWidget);
    toolBar->addAction(userInfoAction);
    toolBar->setPalette(mainPalette);
}
void MainWindow::setToolBarEditor() {
    backAction->setVisible(false);
    addAction->setVisible(false);
    inviteAction->setVisible(false);

    treeShowAction->setVisible(true);
    highlightAction->setVisible(true);
    closeAction->setVisible(true);
    pdfAction->setVisible(true);
}
void MainWindow::setToolBarGrid() {
    if(centralWidget->currentWidget() != editor) {
        treeShowAction->setVisible(false);
        highlightAction->setVisible(false);
        closeAction->setVisible(false);
        pdfAction->setVisible(false);

        backAction->setVisible(false);
        addAction->setVisible(true);
        inviteAction->setVisible(true);
        inviteAction->setDisabled(true);
    }
}
void MainWindow::setToolBarFolderGrid(QString folder) {
    if(centralWidget->currentWidget() != editor) {
        treeShowAction->setVisible(false);
        highlightAction->setVisible(false);
        closeAction->setVisible(false);
        pdfAction->setVisible(false);

        addAction->setVisible(false);
        backAction->setVisible(true);
        inviteAction->setVisible(true);
        inviteAction->setDisabled(true);
    }
}

void MainWindow::changeToolbarProfileImage(const QPixmap& orig) {
    int size = qMax(orig.width(), orig.height());
    QPixmap rounded = QPixmap(size, size);
    rounded.fill(Qt::transparent);
    QPainterPath path;
    path.addEllipse(rounded.rect());
    QPainter painter(&rounded);
    painter.setClipPath(path);
    painter.fillRect(rounded.rect(), Qt::black);
    int x = qAbs(orig.width() - size) / 2;
    int y = qAbs(orig.height() - size) / 2;
    painter.drawPixmap(x, y, orig.width(), orig.height(), orig);
    userInfoAction->setIcon(QIcon(rounded));
}

void MainWindow::editorSettings(SharedEditor* shEditor) {
    editor = new EditorGUI(shEditor, this);

    infoWidget = new InfoWidget(this);
    addUserWidget = new AddUserWidget(this);
    inviteUserWidget = new InviteUserWidget(this);
    uriWidget = new UriWidget(this);

    //widgetEditor->hide();
}

void MainWindow::startSignIn() {
    centralWidget->setCurrentWidget(widgetSignIn);
}

void MainWindow::backToLogIn() {
    centralWidget->setCurrentWidget(loginDialog);
}

void MainWindow::openAddUser(const QString& fileName) {
    addUserWidget->setFile(fileName);
    addUserWidget->setWindowTitle("Invite user to file "+fileName);
    addUserWidget->show();
}

void MainWindow::signInWidgetSetup() {
    widgetSignIn = new SignInWidget(this);
}

void MainWindow::resizeEvent(QResizeEvent *evt) {
    QWidget::resizeEvent(evt);
    dockWidgetTree->setMaximumWidth(this->size().width() / 4);
    dockWidgetTree->setMinimumWidth(this->size().width() / 4);

}

void MainWindow::setStyleSheet() {
//    qApp->setStyleSheet("QWidget {font-family: helvetica}"
//                        "QPushButton {border-style: solid; border-width: 2px; border-color: #8fc1ed; border-radius: 12px; "
//                        "min-width: 4em; padding: 3px; padding-left: 10px; padding-right:10px; font: 9pt; }");
//                        "QPushButton:pressed {background-color: lightblue}");

//    "QLabel {color: white; font: 14pt}");


}

void MainWindow::setUsersList() {
    usersView = new UsersListView(this);
    usersModel  = new UsersListModel(this);
    usersView->setModel(usersModel);

    dockWidgetUsers = new QDockWidget(this);
    dockWidgetUsers->setAllowedAreas(Qt::RightDockWidgetArea );
    dockWidgetUsers->setFeatures(QDockWidget::DockWidgetVerticalTitleBar);
    dockWidgetUsers->setMouseTracking(true);

//    treeShowAction = new QAction();
//    treeShowAction->setIcon(QIcon("./icons/left_tree_menu.png"));
//    toolBar->addAction(treeShowAction);

    dockWidgetUsers->setWindowTitle("Users connected");
    dockWidgetUsers->setWidget(usersView);
    dockWidgetUsers->setPalette(mainPalette);
    auto p = dockWidgetUsers->palette();
    p.setColor(QPalette::Window,QColor("red"));
    dockWidgetUsers->setPalette(p);

    this->addDockWidget(Qt::RightDockWidgetArea,dockWidgetUsers);
    dockWidgetUsers->hide();
}

void MainWindow::setMainPalette() {
//    .dark-primary-color    { background: #303F9F; }
//            .default-primary-color { background: #3F51B5; }
//                .light-primary-color   { background: #C5CAE9; }
//                            .text-primary-color    { color: #FFFFFF; }
//                            .accent-color          { background: #FF9800; }
//                            .primary-text-color    { color: #212121; }
//                            .secondary-text-color  { color: #757575; }
//                            .divider-color         { border-color: #BDBDBD; }

    mainPalette = QGuiApplication::palette();
    mainPalette.setColor(QPalette::Window,QColor("#3F51B5"));
    mainPalette.setColor(QPalette::WindowText,QColor("white"));
    mainPalette.setColor(QPalette::Base,QColor("#C5CAE9"));
    mainPalette.setColor(QPalette::BrightText,QColor("#FF9800"));
    mainPalette.setColor(QPalette::ButtonText,QColor("black"));
    mainPalette.setColor(QPalette::Button,QColor("#FF9800"));



}

void MainWindow::setNumUsers(int n) {
    auto string = QString("Users online: ");
    string.append(QString::number(n));
    numUsers->setText(string);
    if(numUsers->isHidden())
        numUsers->show();
}

void MainWindow::hideNumUsers() {
    numUsers->hide();
}