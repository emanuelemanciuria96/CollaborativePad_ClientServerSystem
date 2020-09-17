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

    setWindowTitle("Shared Editor");
    statusBar = new QStatusBar(this);
    statusBar->showMessage ("");
    toolBar = new QToolBar("Toolbar",this);
    centralWidget = new QStackedWidget(this);

    //    aggiungo gli elementi alla finestra
    this->setStatusBar(statusBar);
    this->addToolBar(toolBar);
    toolBar->setMovable(false);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
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
    // widgetAccount creation
    infoWidgetsSettings();
    //highlightSetup

    signInWidgetSetup();

    setToolBar();
    setToolBarGrid();

    connect(loginDialog, &LoginDialog::acceptLogin, shEditor, &SharedEditor::loginSlot);
    connect(treeView, &FileSystemTreeView::opnFileRequest,shEditor , &SharedEditor::requireFile);
    connect(treeView, &FileSystemTreeView::renFileRequest,shEditor , &SharedEditor::requireFileRename);
    connect(treeView, &FileSystemTreeView::newFileAdded,shEditor , &SharedEditor::requireFileAdd);
    connect(treeView, &FileSystemTreeView::rmvFileRequest,shEditor , &SharedEditor::requireFileDelete);
    connect(gridView, &FileSystemGridView::opnFileRequest,this, &MainWindow::opnFileGrid);
    connect(gridView, &FileSystemGridView::opnFileRequest,shEditor , &SharedEditor::requireFile);
    connect(gridView, &FileSystemGridView::openFolder,this, &MainWindow::setToolBarFolderGrid);
    connect(gridView, &FileSystemGridView::back,this, &MainWindow::setToolBarGrid);
    connect(gridView, &FileSystemGridView::canInvite,this, &MainWindow::changeInviteAction);
    connect(gridView, &FileSystemGridView::renFileRequest,shEditor , &SharedEditor::requireFileRename);
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
    connect(shEditor, &SharedEditor::userInfoArrived, infoWidget, &InfoWidget::loadData);
    connect(infoWidget, &InfoWidget::sendUpdatedInfo, shEditor, &SharedEditor::sendUpdatedInfo);
    connect(loginDialog, &LoginDialog::signIn, this, &MainWindow::startSignIn);
    connect(widgetSignIn, &SignInWidget::backToLogIn, this, &MainWindow::backToLogIn);
    connect(highlightAction, &QAction::triggered, shEditor, &SharedEditor::highlightSymbols);
    connect(closeAction, &QAction::triggered, this, &MainWindow::clsFile);
    connect(closeAction, &QAction::triggered, shEditor, &SharedEditor::requireFileClose);
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

    //    imposto la grandezza della finestra
    auto size = QGuiApplication::primaryScreen()->size();
    this->resize(size.width()*0.7,size.height()*0.7);

    centralWidget->addWidget(loginDialog);
    centralWidget->addWidget(widgetInfoEditC);
    centralWidget->addWidget(widgetEditor);
    centralWidget->addWidget(widgetSignIn);
    centralWidget->addWidget(gridView);


//    this->setCentralWidget(widgetLogin);
}

void MainWindow::loginFinished() {
    centralWidget->setCurrentWidget(gridView);
    centralWidget->setCurrentWidget(widgetEditor);
    widgetEditor->hide();
    toolBar->show();
    gridView->show();
    createMenus();
}
void MainWindow::opnFileGrid(QString fileName) {
    //treeView->constructFromPaths(gridView->getVector());
    setToolBarEditor();
    widgetEditor->show();
    //dockWidgetTree->show();
    gridView->hide();
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
    if(gridView->getState()==gridView->getMainFolder()){
        setToolBarGrid();
        inviteAction->setDisabled(false);
    }else{
        setToolBarFolderGrid(gridView->getState());
    }
    widgetEditor->hide();
    dockWidgetTree->hide();
    gridView->show();
}
void MainWindow::loginSettings() {
//    widgetLogin = new QWidget(this);
//    widgetLogin->setLayout( new QGridLayout(widgetLogin) );
//
//    auto *boxLogin = new QGroupBox(widgetLogin);
    loginDialog = new LoginDialog(this);
//    boxLogin->setLayout(new QVBoxLayout());

    // pinting box
//    QRgb rgbColor = loginBackground.pixel(0,0);

//    QPalette p2{};
//    QLinearGradient grad(0,50,0,0);
//    grad.setColorAt(0,QColor(rgbColor));
//    grad.setColorAt(1,Qt::lightGray);
//    QBrush brush2(grad);
//    p2.setBrush(QPalette::Window,brush2);
//    boxLogin->setAutoFillBackground(true);
//    boxLogin->setPalette(p2);

    /*boxLogin->setStyleSheet("QGroupBox {border: 0px;"
                            "border-radius: 15px;"
                            "margin-top: 1ex;}");
                            */
//    boxLogin->setTitle("login");
    //boxLogin->layout()->addWidget(new QLabel("Please insert your user and password in the following boxes",widgetLogin));
//    boxLogin->layout()->addWidget(loginDialog);

//    dynamic_cast<QGridLayout*>(widgetLogin->layout())->addWidget(boxLogin,1,1,4,1,Qt::AlignCenter);

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
}

void MainWindow::gridFileSystemSettings() {
    gridView = new FileSystemGridView();
}

void MainWindow::setToolBar() {
    //EditorToolbar
    treeShowAction = new QAction();
    treeShowAction->setIcon(QIcon("./icons/left_tree_menu.png"));
    treeShowAction->setVisible(false);
    treeShowAction->setToolTip("Hide tree");
    toolBar->addAction(treeShowAction);

    highlightAction = toolBar->addAction("Highlight");
    highlightAction->setCheckable(true);
    highlightAction->setShortcut(QKeySequence::Replace); //equivale a Ctrl+H
    highlightAction->setStatusTip("Highlight the text entered by different users");
    highlightAction->setIcon(QIcon("./icons/icons8-spotlight-64.png"));
    highlightAction->font().setPointSize(10);
    highlightAction->setToolTip("Highlight the text entered by different users");
    highlightAction->setVisible(false);

    closeAction = new QAction();
    closeAction->setIcon(QIcon("./icons/close.png"));
    closeAction->setVisible(false);
    closeAction->setToolTip("Close file");
    toolBar->addAction(closeAction);

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

}
void MainWindow::setToolBarEditor() {
    backAction->setVisible(false);
    addAction->setVisible(false);
    inviteAction->setVisible(false);

    treeShowAction->setVisible(true);
    highlightAction->setVisible(true);
    closeAction->setVisible(true);
}
void MainWindow::setToolBarGrid() {
    treeShowAction->setVisible(false);
    highlightAction->setVisible(false);
    closeAction->setVisible(false);

    backAction->setVisible(false);
    addAction->setVisible(true);
    inviteAction->setVisible(true);
    inviteAction->setDisabled(true);
}
void MainWindow::setToolBarFolderGrid(QString folder) {
    treeShowAction->setVisible(false);
    highlightAction->setVisible(false);
    closeAction->setVisible(false);

    addAction->setVisible(false);
    backAction->setVisible(true);
    inviteAction->setVisible(true);
    inviteAction->setDisabled(true);
}

void MainWindow::editorSettings(SharedEditor* shEditor) {
    widgetEditor = new QWidget(this);
    widgetEditor->setStyleSheet("QWidget { background: lightGray; }");
    editor = new EditorGUI(shEditor, widgetEditor);
    editor->setStyleSheet("QWidget { background: white; }");
    auto layoutEditor = new QVBoxLayout(widgetEditor);
    layoutEditor->addWidget(editor);
    layoutEditor->setContentsMargins(0,0,0,0);
    addUserWidget = new AddUserWidget(this);
    inviteUserWidget = new InviteUserWidget(this);
    uriWidget = new UriWidget(this);

    widgetEditor->hide();
}

void MainWindow::startSignIn() {
    centralWidget->setCurrentWidget(widgetSignIn);
}

void MainWindow::infoWidgetsSettings() {
    infoWidget = new InfoWidget(this);
    widgetInfoEditC = new QWidget(this);

    infoWidget->hide();
//    QPalette p1{};
//    QImage loginBackground = QImage("./textures/texture_clouds_background.png");
//    QBrush brush1(loginBackground);
//    p1.setBrush(QPalette::Window,brush1);
//    widgetInfoEditC->setPalette(p1);

//    QGroupBox *box = new QGroupBox(widgetInfoEditC);
    infoWidgetEdit = new InfoWidgetEdit(widgetInfoEditC);

//    box->setLayout(new QVBoxLayout());
//    box->layout()->addWidget(infoWidgetEdit);
//    box->layout()->addWidget(new QLabel("prova",box,Qt::Widget));
    auto boxLayout = new QVBoxLayout(widgetInfoEditC);
    boxLayout->addWidget(infoWidgetEdit);
    widgetInfoEditC->setLayout(boxLayout);
//    dynamic_cast<QGridLayout*>(widgetInfoEditC->layout())->addWidget(infoWidgetEdit,0,1,Qt::AlignCenter);
//    dynamic_cast<QGridLayout*>(widgetInfoEditC->layout())->addWidget(new QLabel("prova",widgetInfoEditC,Qt::Widget),0,0,Qt::AlignCenter);
//    dynamic_cast<QGridLayout*>(widgetInfoEditC->layout())->addWidget(new QLabel("prova",widgetInfoEditC,Qt::Widget),0,2,Qt::AlignCenter);
}

void MainWindow::backToLogIn() {
    centralWidget->setCurrentWidget(loginDialog);
}

void MainWindow::openAddUser(const QString& fileName) {
    addUserWidget->setFile(fileName);
    addUserWidget->show();
}


void MainWindow::signInWidgetSetup() {
    widgetSignIn = new SignInWidget(this);
}

void MainWindow::createMenus() {
    auto fileMenu = menuBar()->addMenu("&File");
    auto PDFAct = new QAction(tr("&Export to PDF"), this);
    PDFAct->setStatusTip(tr("Export current file to pdf"));
    connect(PDFAct, &QAction::triggered, editor, &EditorGUI::exportToPdf);
    fileMenu->addAction(PDFAct);
}


void MainWindow::resizeEvent(QResizeEvent *evt) {
    QWidget::resizeEvent(evt);
    QPalette p = palette();
    p.setBrush(QPalette::Window,bkgnd.scaled(centralWidget->size(), Qt::KeepAspectRatioByExpanding));

    QLinearGradient grad(500,500,1000,1000);
    grad.setColorAt(0,QColor("#4b71e3"));
    grad.setColorAt(1,QColor("#87b5ff"));
    QBrush brush2(grad);
//    p.setBrush(QPalette::Window,brush2);

    centralWidget->setAutoFillBackground(true);
    centralWidget->setPalette(p);

    dockWidgetTree->setMaximumWidth(this->size().width() / 4);
    dockWidgetTree->setMinimumWidth(this->size().width() / 4);

}

void MainWindow::setStyleSheet() {
    qApp->setStyleSheet("QWidget {font-family: helvetica}"
                        "QPushButton {border-style: solid; border-width: 2px; border-color: #8fc1ed; border-radius: 12px; "
                        "background-color: white; min-width: 4em; padding: 3px; padding-left: 10px; padding-right:10px; font: 9pt; color: #182c3d;}"
                        "QPushButton:pressed {background-color: lightblue}"
                        "QLabel {color: white; font: 14pt}");


}
