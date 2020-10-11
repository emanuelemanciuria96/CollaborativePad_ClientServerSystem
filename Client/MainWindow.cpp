//
// Created by utente on 06/08/2020.
//

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QDockWidget>
#include "MainWindow.h"

QVector<QString> msgs = {"tree","invite list", "uri insertion"};

MainWindow::MainWindow(SharedEditor* shEditor, QWidget *parent) : QMainWindow(parent) {
    QApplication::setStyle(QStyleFactory::create("window"));
//    for(auto k : QStyleFactory::keys()){
//        std::cout << k.toStdString() << std::endl;
//    }
    bkgnd = QPixmap("./textures/texture_clouds_background.png");
    setMainPalette();
    setPalette(mainPalette);
    setAutoFillBackground(true);
    setWindowTitle("Shared Editor");
    installEventFilter(this);
    //statusBar initialize
    statusBar = new QStatusBar(this);
    numUsers = new QLabel(statusBar);
    numUsers->setText("User connected: 0");
    statusBar->addPermanentWidget(numUsers);
    numUsers->hide();
    statusBar->showMessage ("");
    statusBar->hide();

    toolBar = new QToolBar("Toolbar",this);
    centralWidget = new QStackedWidget(this);
    richTextBar = new QToolBar(this);

    //    aggiungo gli elementi alla finestra
    this->setStatusBar(statusBar);
    this->addToolBar(toolBar);
    addToolBarBreak(Qt::TopToolBarArea);
    this->addToolBar(richTextBar);
    toolBar->setMovable(false);
    toolBar->setMinimumHeight(45);
    toolBar->setIconSize(QSize(45, 45));
    toolBar->hide();

    nullWidg = new QWidget(this);
    richTextBar->setMovable(false);
    richTextBar->setIconSize(QSize(25,25));
    richTextBar->move(toolBar->rect().bottomLeft());
    richTextBar->hide();

    setCentralWidget(centralWidget);
    // tree file system view creation
    treeFileSystemSettings();
    // grid file system view creation
    gridFileSystemSettings();
    // login creation
    loginSettings();
    // editor creation
    editorSettings(shEditor);
    // invite list creation
    inviteUserListSetup();
    // uri widget creation
    uriWidgetSetup();

    signInWidgetSetup();
    setUsersList();

    setToolBar();
    setToolBarGrid();
    setRichTextBar();
    setStyleSheet();

    connect(loginDialog, &LoginDialog::acceptLogin, shEditor, &SharedEditor::loginSlot);
    connect(treeView, &FileSystemTreeView::opnFileRequest,shEditor , &SharedEditor::requireFile);
    connect(treeView, &FileSystemTreeView::renFileRequest,shEditor , &SharedEditor::requireFileRename);
    connect(treeView, &FileSystemTreeView::newFileAdded,shEditor , &SharedEditor::requireFileAdd);
    connect(treeView, &FileSystemTreeView::rmvFileRequest,shEditor , &SharedEditor::requireFileDelete);
    connect(treeView, &FileSystemTreeView::newFileUpdateGrid, gridView, &FileSystemGridView::constructFromPaths);
    connect(treeView, &FileSystemTreeView::renFileRequest,gridView , &FileSystemGridView::remoteRenameFile);
    connect(treeView, &FileSystemTreeView::rmvFileRequest,gridView , &FileSystemGridView::remoteDeleteFile);
    connect(gridView, &FileSystemGridView::rmvFileRequest,shEditor , &SharedEditor::requireFileDelete);
    connect(gridView, &FileSystemGridView::opnFileRequest,shEditor , &SharedEditor::requireFile);
    connect(gridView, &FileSystemGridView::openFolder,this, &MainWindow::setToolBarFolderGrid);
    connect(gridView, &FileSystemGridView::back,this, &MainWindow::setToolBarGrid);
    connect(gridView, &FileSystemGridView::canInvite,this, &MainWindow::changeInviteAction);
    connect(treeView, &FileSystemTreeView::canInvite,this, &MainWindow::changeInviteAction);
    connect(gridView, &FileSystemGridView::canDelete,this, &MainWindow::changeDeleteAction);
    connect(gridView, &FileSystemGridView::renFileRequest,shEditor , &SharedEditor::requireFileRename);
    connect(gridView, &FileSystemGridView::renFileRequest,treeView , &FileSystemTreeView::editFileName);
    connect(gridView, &FileSystemGridView::newFileAdded,shEditor , &SharedEditor::requireFileAdd);
    connect(shEditor, &SharedEditor::openTextEditor,this, &MainWindow::opnFileGrid);
    connect(shEditor, &SharedEditor::hideEditor, this, &MainWindow::hideEditor);
    connect(shEditor, &SharedEditor::transparentForMouse,this, &MainWindow::transparentForMouse);
    connect(shEditor, &SharedEditor::fileNameEdited, treeView, &FileSystemTreeView::editFileName);
    connect(shEditor, &SharedEditor::fileDeletion, treeView, &FileSystemTreeView::remoteFileDeletion);
    connect(shEditor, &SharedEditor::fileDeletion, gridView, &FileSystemGridView::remoteDeleteFile);
    connect(shEditor, &SharedEditor::loginAchieved, this, &MainWindow::loginFinished);
    connect(shEditor, &SharedEditor::loginError, loginDialog, &LoginDialog::slotLoginError);
    connect(shEditor, &SharedEditor::symbolsChanged, editor, &EditorGUI::updateSymbols);
    connect(shEditor, &SharedEditor::symbolsChanged, highlightEditor, &EditorGUI::updateSymbols);
    connect(shEditor, &SharedEditor::remoteCursorPosChanged, editor, &EditorGUI::updateRemoteCursorPos);
    connect(shEditor, &SharedEditor::remoteCursorPosChanged, highlightEditor, &EditorGUI::updateRemoteCursorPos);
    connect(shEditor, &SharedEditor::removeCursor, editor, &EditorGUI::removeCursor);
    connect(shEditor, &SharedEditor::removeCursor, highlightEditor, &EditorGUI::removeCursor);
    connect(shEditor, &SharedEditor::deleteAllText, editor, &EditorGUI::deleteAllText);
    connect(shEditor, &SharedEditor::deleteAllText, highlightEditor, &EditorGUI::deleteAllText);
    connect(shEditor, &SharedEditor::filePathsArrived, treeView, &FileSystemTreeView::constructFromPaths);
    connect(shEditor, &SharedEditor::filePathsArrived, gridView, &FileSystemGridView::constructFromPaths);
    connect(gridView, &FileSystemGridView::newFileUpdateTree, treeView, &FileSystemTreeView::constructFromPaths);
    connect(shEditor, &SharedEditor::userInfoArrived, infoWidget, &InfoWidget::loadData);
    connect(infoWidget, &InfoWidget::sendUpdatedInfo, shEditor, &SharedEditor::sendUpdatedInfo);
    connect(loginDialog, &LoginDialog::signIn, this, &MainWindow::startSignIn);
    connect(widgetSignIn, &SignInWidget::backToLogIn, this, &MainWindow::backToLogIn);
//    connect(highlightAction, &QAction::triggered, shEditor, &SharedEditor::highlightSymbols);
    connect(highlightAction, &QAction::triggered, this, &MainWindow::highlight);

    // TODO: cambiare la connect di sotto per l'undo su highlight
//    connect(highlightAction, &QAction::triggered, [this](bool chacked=false){ editor->textEdit->document()->clearUndoRedoStacks(); });
    // TODO: ...
    connect(shEditor, &SharedEditor::setCharFormat, editor, &EditorGUI::setCharFormat);
    connect(shEditor, &SharedEditor::setCharFormat, highlightEditor, &EditorGUI::setCharFormat);
    connect(shEditor, &SharedEditor::returnToGrid, this, &MainWindow::clsFile);
    connect(closeAction, &QAction::triggered, shEditor, &SharedEditor::requireFileClose);
    connect(pdfAction, &QAction::triggered, editor, &EditorGUI::exportToPdf);
    connect(pdfAction, &QAction::triggered, highlightEditor, &EditorGUI::exportToPdf);
    connect(addAction, &QAction::triggered, gridView, &FileSystemGridView::addFile);
    connect(backAction, &QAction::triggered, gridView, &FileSystemGridView::reloadBack);
//    connect(shEditor, &SharedEditor::highlight, editor, &EditorGUI::highlight);
    connect(widgetSignIn, &SignInWidget::registerRequest, shEditor, &SharedEditor::sendRegisterRequest);
    connect(addUserWidget, &AddUserWidget::searchUser, shEditor, &SharedEditor::searchUser);
    connect(shEditor, &SharedEditor::searchUserResult, addUserWidget, &AddUserWidget::searchUserResult);
    connect(shEditor, &SharedEditor::inviteResultArrived, addUserWidget, &AddUserWidget::inviteResultArrived);
    connect(addUserWidget, &AddUserWidget::setStatusBarText, statusBar, &QStatusBar::showMessage);
    connect(addUserWidget, &AddUserWidget::submitInvite, shEditor, &SharedEditor::submitInvite);
    connect(treeView, &FileSystemTreeView::inviteRequest, this, &MainWindow::openAddUser);
    connect(inviteAction, &QAction::triggered, gridView, &FileSystemGridView::invite);
    connect(deleteAction, &QAction::triggered, gridView, &FileSystemGridView::deleteCurrent);
    connect(gridView, &FileSystemGridView::inviteRequest, this, &MainWindow::openAddUser);
    connect(shEditor, &SharedEditor::inviteListArrived, inviteUserWidget, &InviteUserWidget::inviteListArrived);
    connect(inviteUserWidget, &InviteUserWidget::sendInviteAnswer, shEditor, &SharedEditor::sendInviteAnswer);
    connect(shEditor, &SharedEditor::fileNameEdited, inviteUserWidget, &InviteUserWidget::editFileName);
    connect(shEditor, &SharedEditor::fileNameEdited, gridView, &FileSystemGridView::remoteRenameFile);
    connect(shEditor, &SharedEditor::fileNameEdited, addUserWidget, &AddUserWidget::editFileName);
    connect(shEditor, &SharedEditor::fileDeletion, inviteUserWidget, &InviteUserWidget::processFileDeleted);
    connect(gridView, &FileSystemGridView::rmvFileRequest, treeView, &FileSystemTreeView::remoteFileDeletion);
    connect(uriWidget, &UriWidget::submitUri, shEditor, &SharedEditor::submitUri);
    connect(shEditor, &SharedEditor::uriResultArrived, uriWidget, &UriWidget::uriResultArrived);
    connect(uriWidget, &UriWidget::setStatusBarText, statusBar, &QStatusBar::showMessage);
    connect(shEditor, &SharedEditor::fsNameArrived, addUserWidget, &AddUserWidget::fsNameArrived);
    connect(addUserWidget, &AddUserWidget::searchFsName, shEditor, &SharedEditor::searchFsName);
    connect(treeView, &FileSystemTreeView::opnFileRequest, editor, &EditorGUI::setCurrentFileName);
    connect(treeView, &FileSystemTreeView::opnFileRequest, highlightEditor, &EditorGUI::setCurrentFileName);
    connect(gridView, &FileSystemGridView::opnFileRequest, editor, &EditorGUI::setCurrentFileName);
    connect(gridView, &FileSystemGridView::opnFileRequest, highlightEditor, &EditorGUI::setCurrentFileName);
    connect(treeView, &FileSystemTreeView::opnFileRequest, gridView, &FileSystemGridView::selectFile);
    connect(userInfoAction, &QAction::triggered, this, &MainWindow::setInfoWidget);
    connect(uriAction, &QAction::triggered, [this](){showHideLeftDock(uri);} );
    connect(infoWidget, &InfoWidget::imageChanged, this, &MainWindow::changeToolbarProfileImage);
    connect(inviteListAction, &QAction::triggered, [this](){showHideLeftDock(invitelist);});
    connect(treeShowAction, &QAction::triggered,[this](){showHideLeftDock(tree);});
    connect(editor, &EditorGUI::setNumUsers, this, &MainWindow::setNumUsers);
    connect(highlightEditor, &EditorGUI::setNumUsers, this, &MainWindow::setNumUsers);
    connect(editor, &EditorGUI::userQuery,shEditor,&SharedEditor::obtainUser);
    connect(highlightEditor, &EditorGUI::userQuery,shEditor,&SharedEditor::obtainUser);
    connect(shEditor, &SharedEditor::setNumUsers, this, &MainWindow::setNumUsers);
    connect(shEditor, &SharedEditor::hideNumUsers, this, &MainWindow::hideNumUsers);
    connect(shEditor, &SharedEditor::addUser, usersList, &UsersList::addUser);
    connect(shEditor, &SharedEditor::removeUser, usersList, &UsersList::removeUser);
    connect(shEditor, &SharedEditor::userNameArrived, editor, &EditorGUI::recordUserWriter);
    connect(shEditor, &SharedEditor::userNameArrived, highlightEditor, &EditorGUI::recordUserWriter);
    connect(shEditor, &SharedEditor::flushFileWriters, editor, &EditorGUI::flushFileWriters);
    connect(shEditor, &SharedEditor::flushFileWriters, highlightEditor, &EditorGUI::flushFileWriters);
    connect(shEditor, &SharedEditor::flushFileWriters, usersList, &UsersList::clear);
    connect(addUserWidget, &AddUserWidget::closing, this, &MainWindow::transparentForMouse);
    connect(treeView, &FileSystemTreeView::inviteRequest, this, &MainWindow::transparentForMouse);
    connect(gridView, &FileSystemGridView::inviteRequest, this, &MainWindow::transparentForMouse);
    connect(infoWidget, &InfoWidget::backPressed, this, &MainWindow::setInfoWidget);
    connect(infoWidget, &InfoWidget::openInfoEdit, this, &MainWindow::openInfoEdit);
    connect(infoWidgetEdit, &InfoWidgetEdit::updateInfo, infoWidget, &InfoWidget::updateInfo);
    connect(infoWidgetEdit, &InfoWidgetEdit::backToInfoWidget, this, [this](){centralWidget->setCurrentWidget(infoWidget);});
    connect(inviteUserWidget, &InviteUserWidget::inviteNumberModified, this, [this](int n){setInviteListIcon(n);});
    connect(usersList, &UsersList::setUserInfo, this, &MainWindow::setInfoUsersListWidget);
    connect(infoUsersListWidget, &InfoUsersListWidget::backPressed, this, &MainWindow::setInfoUsersListWidget);
    connect(editor->textEdit, &MyTextEdit::copyAvailable, this,[this](bool b){copyAction->setDisabled(!b);cutAction->setDisabled(!b);});
    connect(highlightEditor->textEdit, &MyTextEdit::copyAvailable, this,[this](bool b){copyAction->setDisabled(!b);cutAction->setDisabled(!b);});

    connect(QApplication::clipboard(), &QClipboard::dataChanged, this, &MainWindow::clipboardDataChanged);
    connect(editor->textEdit->document(), &QTextDocument::undoAvailable,undoAction, &QAction::setEnabled);
    connect(highlightEditor->textEdit->document(), &QTextDocument::undoAvailable,undoAction, &QAction::setEnabled);
    connect(editor->textEdit->document(), &QTextDocument::redoAvailable,redoAction, &QAction::setEnabled);
    connect(highlightEditor->textEdit->document(), &QTextDocument::redoAvailable,redoAction, &QAction::setEnabled);
    connect(pasteAction, &QAction::triggered, editor->textEdit, &MyTextEdit::paste);
    connect(copyAction, &QAction::triggered, editor->textEdit, &QTextEdit::copy);
    connect(cutAction, &QAction::triggered, editor->textEdit, &QTextEdit::cut);
    connect(redoAction, &QAction::triggered, editor->textEdit, &QTextEdit::redo);
    connect(undoAction, &QAction::triggered, editor->textEdit, &MyTextEdit::undo);
//    connect(pasteAction, &QAction::triggered, highlightEditor->textEdit, &MyTextEdit::paste);
//    connect(copyAction, &QAction::triggered, highlightEditor->textEdit, &QTextEdit::copy);
//    connect(cutAction, &QAction::triggered, highlightEditor->textEdit, &QTextEdit::cut);
//    connect(redoAction, &QAction::triggered, highlightEditor->textEdit, &QTextEdit::redo);
//    connect(undoAction, &QAction::triggered, highlightEditor->textEdit, &QTextEdit::undo);
    connect(boldAction, &QAction::triggered, editor, &EditorGUI::setBold);
    connect(italicAction, &QAction::triggered, editor, &EditorGUI::setItalic);
    connect(underlineAction, &QAction::triggered, editor, &EditorGUI::setUnderline);
    connect(textColorAction, &QAction::triggered, editor, &EditorGUI::textColor);
    connect(editor, &EditorGUI::colorChanged, this, &MainWindow::colorChanged);
    connect(editor, &EditorGUI::fontChanged, this, &MainWindow::fontChanged);
    connect(comboSize, SIGNAL(activated(const QString&)), editor, SLOT(textSize(const QString&)));
    connect(comboFont, SIGNAL(activated(const QString&)), editor, SLOT(textFamily(const QString&)));
//    connect(boldAction, &QAction::toggled, highlightEditor, &EditorGUI::setBold);
//    connect(italicAction, &QAction::toggled, highlightEditor, &EditorGUI::setItalic);
//    connect(underlineAction, &QAction::toggled, highlightEditor, &EditorGUI::setUnderline);

    connect(editor, &EditorGUI::updateOther, this, &MainWindow::recvEditorUpdate);
    connect(highlightEditor, &EditorGUI::updateOther, this, &MainWindow::recvEditorUpdate);

    connect(shEditor, &SharedEditor::fileLoaded, highlightEditor, &EditorGUI::loadHighlights);

    //    imposto la grandezza della finestra
    auto size = QGuiApplication::primaryScreen()->size();
    this->resize(size.width()*0.7,size.height()*0.7);

    centralWidget->addWidget(loginDialog);
    centralWidget->addWidget(editor);
    centralWidget->addWidget(highlightEditor);
    centralWidget->addWidget(infoWidget);
    centralWidget->addWidget(infoWidgetEdit);
    centralWidget->addWidget(infoUsersListWidget);
    centralWidget->addWidget(widgetSignIn);
    centralWidget->addWidget(gridView);
    centralWidget->addWidget(nullWidg);
    setCorner(Qt::TopLeftCorner,Qt::LeftDockWidgetArea);
    setCorner(Qt::TopRightCorner,Qt::RightDockWidgetArea);
    lastCentral = nullptr;
    lastDock = nullptr;
}

void MainWindow::transparentForMouse() {
    bool var = !toolBar->testAttribute(Qt::WA_TransparentForMouseEvents);
    toolBar->setAttribute(Qt::WA_TransparentForMouseEvents, var);
    gridView->setAttribute(Qt::WA_TransparentForMouseEvents, var);
    treeView->setAttribute(Qt::WA_TransparentForMouseEvents, var);
}

void MainWindow::loginFinished() {
    centralWidget->setCurrentWidget(gridView);
    toolBar->show();
    statusBar->show();
    gridView->show();

}

void MainWindow::opnFileGrid(QString &fileName) {
    editor->textEdit->document()->clearUndoRedoStacks();

    setToolBarEditor();
    centralWidget->setCurrentWidget(editor);
    dockWidgetUsers->show();
    richTextBar->show();
    auto palette = this->palette();
//    palette.setColor(QPalette::Window,QColor("lightgray"));
    palette.setColor(QPalette::Base,QColor("white"));
    setPalette(palette);

    this->setCursor(QCursor(Qt::ArrowCursor));
    statusBar->clearMessage();
    delete spinner;

}

void MainWindow::changeInviteAction(bool state){
    inviteAction->setDisabled(!state);
    if(state){
        inviteAction->setToolTip("Invite user");
    }else{
        inviteAction->setToolTip("");
    }
}
void MainWindow::changeDeleteAction(bool state){
    deleteAction->setDisabled(!state);
    if(state){
        deleteAction->setToolTip("Delete file");
    }else{
        deleteAction->setToolTip("");
    }
}

void MainWindow::clsFile() {
    dockWidgetUsers->hide();
    richTextBar->hide();
    centralWidget->setCurrentWidget(gridView);
    leftDockWidgets[tree]->hide();
    if(gridView->getState()==gridView->getMainFolder()){
        setToolBarGrid();
        inviteAction->setDisabled(false);
    }else{
        setToolBarFolderGrid(gridView->getState());
    }
    gridView->show();
    if(highlightAction->isChecked()){
//        highlightAction->trigger();
        highlightAction->setChecked(false);
    }
}

void MainWindow::loginSettings() {
    loginDialog = new LoginDialog(this);
}


void MainWindow::treeFileSystemSettings() {
    leftDockWidgets.insert( tree, new QDockWidget(tr("files"),this) );
    leftDockWidgets[tree]->setAllowedAreas(Qt::LeftDockWidgetArea );
    leftDockWidgets[tree]->setFeatures(QDockWidget::DockWidgetClosable);
    leftDockWidgets[tree]->setMouseTracking(true);

    leftDockWidgets[tree]->setTitleBarWidget(new QWidget());

    treeView = new FileSystemTreeView(leftDockWidgets[tree]);
    leftDockWidgets[tree]->setWidget(treeView);

    this->addDockWidget(Qt::LeftDockWidgetArea,leftDockWidgets[tree]);
    leftDockWidgets[tree]->hide();

}

void MainWindow::inviteUserListSetup() {
    leftDockWidgets.insert(invitelist,new QDockWidget(tr("invite"),this));
    leftDockWidgets[invitelist]->setAllowedAreas(Qt::LeftDockWidgetArea );
    leftDockWidgets[invitelist]->setFeatures(QDockWidget::DockWidgetClosable);
    leftDockWidgets[invitelist]->setMouseTracking(true);

    leftDockWidgets[invitelist]->setTitleBarWidget(new QWidget());
    inviteUserWidget = new InviteUserWidget(this);
    leftDockWidgets[invitelist]->setWidget(inviteUserWidget);

    this->addDockWidget(Qt::LeftDockWidgetArea,leftDockWidgets[invitelist]);
    leftDockWidgets[invitelist]->hide();
}

void MainWindow::uriWidgetSetup() {
    leftDockWidgets.insert(uri,new QDockWidget(tr("uri"),this));
    leftDockWidgets[uri]->setAllowedAreas(Qt::LeftDockWidgetArea );
    leftDockWidgets[uri]->setFeatures(QDockWidget::DockWidgetClosable);
    leftDockWidgets[uri]->setMouseTracking(true);

    leftDockWidgets[uri]->setTitleBarWidget(new QWidget());
    uriWidget = new UriWidget(this);
    leftDockWidgets[uri]->setWidget(uriWidget);

    this->addDockWidget(Qt::LeftDockWidgetArea,leftDockWidgets[uri]);
    leftDockWidgets[uri]->hide();

}

void MainWindow::gridFileSystemSettings() {
    gridView = new FileSystemGridView();
//    gridView->setPalette(mainPalette);
}

void MainWindow::setToolBar() {
    //EditorToolbar
    backAction = new QAction();
    backAction->setIcon(QIcon("./icons/grid_back_icon.png"));
    backAction->setVisible(false);
    backAction->setToolTip("Back");
    toolBar->addAction(backAction);

    addAction = new QAction();
    addAction->setIcon(QIcon("./icons/add_file_icon.png"));
    addAction->setVisible(false);
    addAction->setToolTip("New file");
    toolBar->addAction(addAction);

    deleteAction = new QAction();
    deleteAction->setIcon(QIcon("./icons/delete_file_icon.png"));
    deleteAction->setVisible(false);
    deleteAction->setToolTip("Delete file");
    toolBar->addAction(deleteAction);

    closeAction = new QAction();
    closeAction->setIcon(QIcon("./icons/close.png"));
    closeAction->setVisible(false);
    closeAction->setToolTip("Close file");
    toolBar->addAction(closeAction);

    QAction* separator1 = toolBar->addSeparator();
    separator1->setObjectName("separator1");

    treeShowAction = new QAction();
    treeShowAction->setIcon(QIcon("./icons/left_tree_menu.png"));
    treeShowAction->setVisible(false);
    treeShowAction->setToolTip("Show tree");
    toolBar->addAction(treeShowAction);

    inviteListAction = new QAction();
    setInviteListIcon();
    inviteListAction->setVisible(true);
    inviteListAction->setToolTip("Show invites list");
    toolBar->addAction(inviteListAction);

    highlightAction=new QAction();
    highlightAction->setCheckable(true);
    highlightAction->setShortcut(QKeySequence::Replace); //equivale a Ctrl+H
    highlightAction->setIcon(QIcon("./icons/highlight.png"));
    highlightAction->setToolTip("Highlight the text entered by different users");
    highlightAction->setVisible(false);
    toolBar->addAction(highlightAction);

    uriAction = new QAction();
    uriAction->setIcon(QIcon("./icons/uri_icon.png"));
    uriAction->setVisible(true);
    uriAction->setToolTip("Add a file inserting a URI");
    toolBar->addAction(uriAction);

    inviteAction = new QAction();
    inviteAction->setIcon(QIcon("./icons/grid_invite_icon.png"));
    toolBar->addAction(inviteAction);

    QAction* separator2 = toolBar->addSeparator();
    separator1->setObjectName("separator2");

    undoAction = new QAction();
    undoAction->setIcon(QIcon("./icons/undo_icon.png"));
    undoAction->setVisible(true);
    undoAction->setDisabled(true);
    undoAction->setToolTip("Undo");
    toolBar->addAction(undoAction);

    redoAction = new QAction();
    redoAction->setIcon(QIcon("./icons/redo_icon.png"));
    redoAction->setVisible(true);
    redoAction->setDisabled(true);
    redoAction->setToolTip("Redo");
    toolBar->addAction(redoAction);

    cutAction = new QAction();
    cutAction->setIcon(QIcon("./icons/cut_icon.png"));
    cutAction->setVisible(true);
    cutAction->setDisabled(true);
    cutAction->setToolTip("Cut");
    toolBar->addAction(cutAction);

    copyAction = new QAction();
    copyAction->setIcon(QIcon("./icons/copy_icon.png"));
    copyAction->setVisible(true);
    copyAction->setDisabled(true);
    copyAction->setToolTip("Copy");
    toolBar->addAction(copyAction);

    pasteAction = new QAction();
    pasteAction->setIcon(QIcon("./icons/paste_icon.png"));
    pasteAction->setVisible(true);
    clipboardDataChanged();
    pasteAction->setToolTip("Paste");
    toolBar->addAction(pasteAction);

    QAction* separator3 = toolBar->addSeparator();
    separator1->setObjectName("separator3");

    pdfAction = new QAction();
    pdfAction->setIcon(QIcon("./icons/pdf.png"));
    pdfAction->setVisible(false);
    pdfAction->setToolTip("Save as pdf");
    toolBar->addAction(pdfAction);

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
}

void MainWindow::setToolBarEditor() {
    backAction->setVisible(false);

    addAction->setVisible(true);
    deleteAction->setVisible(true);
    treeShowAction->setVisible(true);
    highlightAction->setVisible(true);
    closeAction->setVisible(true);
    pdfAction->setVisible(true);

    undoAction->setVisible(true);
    redoAction->setVisible(true);
    cutAction->setVisible(true);
    copyAction->setVisible(true);
    pasteAction->setVisible(true);
}

void MainWindow::setToolBarGrid() {
    if(centralWidget->currentWidget() != editor) {
        treeShowAction->setVisible(false);
        highlightAction->setVisible(false);
        closeAction->setVisible(false);
        pdfAction->setVisible(false);

        backAction->setVisible(false);
        addAction->setVisible(true);
        deleteAction->setVisible(true);
        deleteAction->setDisabled(true);
        inviteAction->setDisabled(true);

        undoAction->setVisible(false);
        redoAction->setVisible(false);
        cutAction->setVisible(false);
        copyAction->setVisible(false);
        pasteAction->setVisible(false);
    }
}

void MainWindow::setToolBarFolderGrid(QString folder) {
    if(centralWidget->currentWidget() != editor) {
        treeShowAction->setVisible(false);
        highlightAction->setVisible(false);
        closeAction->setVisible(false);
        pdfAction->setVisible(false);

        addAction->setVisible(false);
        deleteAction->setVisible(true);
        deleteAction->setDisabled(true);

        backAction->setVisible(true);
        inviteAction->setDisabled(true);

        undoAction->setVisible(false);
        redoAction->setVisible(false);
        cutAction->setVisible(false);
        copyAction->setVisible(false);
        pasteAction->setVisible(false);
    }
}

void MainWindow::setInviteListIcon(int num) {
    QString path="./icons/invite_list_icon.png";
    QString path2="./icons/bedge_invite_list_icon.png";
    if(num<1){
        inviteListAction->setIcon(QIcon(path));
        return;
    }
    const QImage orig = QImage(path2);
    int size = qMax(orig.width(), orig.height());
    QPixmap rounded = QPixmap(size, size);
    rounded.fill(Qt::transparent);
    QPainter painter(&rounded);
    painter.drawImage(QRect(0, -5, orig.width(), orig.height()), orig);
    painter.setPen(Qt::white);
    QFont font = painter.font();
    font.setPointSize(font.pointSize() * 4.5);
    painter.setFont(font);
    if(num>99) {
        painter.drawText(120, 65, QString::number(99));
    }else if(num>9){
        painter.drawText(120, 65, QString::number(num));
    }else{
        painter.drawText(140, 65, QString::number(num));
    }
    inviteListAction->setIcon(QIcon(rounded));
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
    editor = new EditorGUI(shEditor, false, this);
    highlightEditor = new EditorGUI(shEditor, true, this);
    infoWidget = new InfoWidget(this);
    infoWidgetEdit = new InfoWidgetEdit(this);
    infoUsersListWidget = new InfoUsersListWidget(this);
    addUserWidget = new AddUserWidget(this);
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

    leftDockWidgets[tree]->setMaximumWidth(this->size().width() / 5);
    leftDockWidgets[tree]->setMinimumWidth(this->size().width() / 5);
    leftDockWidgets[invitelist]->setMaximumWidth(this->size().width() / 3);
    leftDockWidgets[invitelist]->setMinimumWidth(this->size().width() / 3);
    leftDockWidgets[uri]->setMaximumWidth(this->size().width() / 5);
    leftDockWidgets[uri]->setMinimumWidth(this->size().width() / 5);
    leftDockWidgets[uri]->setMaximumHeight(this->size().height() / 5);
    leftDockWidgets[uri]->setMinimumHeight(this->size().height() / 5);

    auto p = palette();
    gradient->setCenter(size().width() / 2, size().height() / 2);
    auto brush = QBrush(*gradient);
    p.setBrush(QPalette::Window, brush);
    setPalette(p);
}

void MainWindow::setStyleSheet() {
    qApp->setStyleSheet("QWidget {font-family: helvetica}"
                        "QToolBar {background:#F1F1F1; }"
                        "QStatusBar {background-color: #F1F1F1; border-top:1px solid #d2d2d2}"
                        "QToolButton {padding:4}"
                        "QPushButton {font: 10pt; padding: 8; padding-right:25; padding-left:25; border-style: none; background:#3A70D5; color:white}");

    dockWidgetUsers->titleBarWidget()->setStyleSheet("font:10pt; font-family: helvetica; color:#4F78C3");
    dockWidgetUsers->setStyleSheet("background: rgba(0,0,0,0.1); border:none; padding:8");
    inviteUserWidget->setStyleSheet("padding:0; margin:0;");
    for(auto d : leftDockWidgets) {
        d->setStyleSheet("QTreeWidget {background: rgba(0,0,0,0.1); border:none; padding:8;}");
    }
}


void MainWindow::setUsersList() {
    usersList = new UsersList(this);

    dockWidgetUsers = new QDockWidget(this);
    dockWidgetUsers->setAllowedAreas(Qt::RightDockWidgetArea );
    dockWidgetUsers->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dockWidgetUsers->setFixedWidth(150);
//    dockWidgetUsers->setMouseTracking(true);

    auto l = new QLabel("Users connected");
    dockWidgetUsers->setTitleBarWidget(l);
    dockWidgetUsers->setWidget(usersList);
    this->addDockWidget(Qt::RightDockWidgetArea,dockWidgetUsers);
    dockWidgetUsers->hide();
}

void MainWindow::setMainPalette() {
    mainPalette = QGuiApplication::palette();

//    mainPalette.setColor(QPalette::WindowText,QColor("white"));
//    mainPalette.setColor(QPalette::Base,QColor("#F1F1F1"));
//    mainPalette.setColor(QPalette::BrightText,QColor("#FF9800"));
//    mainPalette.setColor(QPalette::ButtonText,QColor("black"));
//    mainPalette.setColor(QPalette::Button,QColor("#90e0ef"));

    gradient = new QConicalGradient(QPointF(size().width()/2,size().height()/2),45);
    gradient->setColorAt(0, QColor("#E6D0E2")); //rosso
    gradient->setColorAt(0.25, QColor("#D0D7E6"));  //blu
    gradient->setColorAt(0.5, QColor("#E6DFD0")); //giallo
    gradient->setColorAt(0.75, QColor("#D0E6D4"));  //verde
    gradient->setColorAt(1, QColor("#E6D0E2"));

//    brush = new QBrush(*gradient);
//    mainPalette.setBrush(QPalette::Window,*brush);
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

void MainWindow::showHideLeftDock(dock_type dock) {

    if(leftDockWidgets[dock]->isHidden()) {
        for( auto d:leftDockWidgets) d->hide();
        leftDockWidgets[dock]->show();
        treeShowAction->setToolTip("Hide "+msgs[dock]);
        treeShowAction->setIcon(QIcon("./icons/hide_left_tree_menu.png"));
        lastDock = leftDockWidgets[dock];
    }else {
        leftDockWidgets[dock]->hide();

        treeShowAction->setToolTip("Show "+msgs[dock]);
        treeShowAction->setIcon(QIcon("./icons/left_tree_menu.png"));
        lastDock = nullptr;
    }
}

void MainWindow::setInfoWidget() {
    if(centralWidget->currentWidget() != infoWidget) {
        lastCentral = centralWidget->currentWidget();
        centralWidget->setCurrentWidget(infoWidget);
        toolBar->hide();
        dockWidgetUsers->hide();
        if (lastDock != nullptr)
            lastDock->hide();
    } else {
        centralWidget->setCurrentWidget(lastCentral);
        toolBar->show();
        if (lastCentral == editor)
            dockWidgetUsers->show();
        if (lastDock != nullptr)
            lastDock->show();
    }
}

void MainWindow::setInfoUsersListWidget(const QPixmap& image, const QString& nickname, const QString& name, const QString& email) {
    if(centralWidget->currentWidget() != infoUsersListWidget) {
        infoUsersListWidget->setData(image, nickname, name, email);
        lastCentral = centralWidget->currentWidget();
        centralWidget->setCurrentWidget(infoUsersListWidget);
        toolBar->hide();
        dockWidgetUsers->hide();
        if (lastDock != nullptr)
            lastDock->hide();
    } else {
        centralWidget->setCurrentWidget(lastCentral);
        toolBar->show();
        if (lastCentral == editor)
            dockWidgetUsers->show();
        if (lastDock != nullptr)
            lastDock->show();
    }
}

void MainWindow::openInfoEdit(const QPixmap& image, const QString& nickname, const QString& name, const QString& email) {
    infoWidgetEdit->setImage(&image);
    infoWidgetEdit->setName(name);
    infoWidgetEdit->setEmail(email);
    infoWidgetEdit->setUser(nickname);
    centralWidget->setCurrentWidget(infoWidgetEdit);
}


void MainWindow::hideEditor(QString& fileName) {
     if(centralWidget->currentWidget()!=gridView)
         centralWidget->setCurrentWidget(nullWidg);

     spinner = new QLabel();
     auto gif = new QMovie("./gifs/ajax-loader.gif");
     gif->setScaledSize(QSize(20,20));
     spinner->setMovie(gif);
     statusBar->addWidget(spinner,3);
     statusBar->showMessage("    Loading file "+fileName,-1);
     spinner->movie()->start();
     this->setCursor(QCursor(Qt::WaitCursor));

}

void MainWindow::setRichTextBar() {
    //EditorToolbar
    boldAction = new QAction();
    boldAction->setIcon(QIcon("./icons/bold.png"));
    boldAction->setCheckable(true);
    boldAction->setToolTip("Bold");
    richTextBar->addAction(boldAction);

    italicAction = new QAction();
    italicAction->setIcon(QIcon("./icons/italic.png"));
    italicAction->setCheckable(true);
    italicAction->setToolTip("Bold");
    richTextBar->addAction(italicAction);

    underlineAction = new QAction();
    underlineAction->setIcon(QIcon("./icons/underline.png"));
    underlineAction->setCheckable(true);
    underlineAction->setToolTip("Bold");
    richTextBar->addAction(underlineAction);

    comboSize = new QComboBox();
    comboSize->setToolTip("Text size");
    const QList<int> standardSizes = QFontDatabase::standardSizes();
    for (int size : standardSizes)
        comboSize->addItem(QString::number(size));
    comboSize->setCurrentIndex(6);
    richTextBar->addWidget(comboSize);

    comboFont = new QFontComboBox();
    comboFont->setToolTip("Text font");
    comboFont->setEditable(false);
    richTextBar->addWidget(comboFont);

    QStringList list{"Arial","Arial Black","Comic Sans MS", "Courier","Georgia","Impact","Tahoma","Times New Roman","Trebuchet MS","Verdana"};
    for(int i = 0; i < comboFont->count(); i++) {
        if(!list.contains(comboFont->itemText(i))){
            comboFont->removeItem(i);
            i--;
        }
    }
    comboFont->setCurrentIndex(7);

    textColorAction = new QAction();
    QPixmap pix(16, 16);
    pix.fill(Qt::black);
    textColorAction->setIcon(QIcon(pix));
    textColorAction->setToolTip("Text color");
    richTextBar->addAction(textColorAction);
}

void MainWindow::colorChanged(const QColor &c)
{
    QPixmap pix(16, 16);
    pix.fill(c);
    textColorAction->setIcon(pix);
}

void MainWindow::highlight(bool checked) {
    if(checked) {
        highlightEditor->setVerticalScrollValue(editor->getVerticalScrollValue());
        highlightEditor->setHorizontalScrollValue(editor->getHorizontalScrollValue());
        centralWidget->setCurrentWidget(highlightEditor);
        std::cout << "highlightEditor setted" << std::endl;
    }
    else {
        editor->setVerticalScrollValue(highlightEditor->getVerticalScrollValue());
        editor->setHorizontalScrollValue(highlightEditor->getHorizontalScrollValue());
        centralWidget->setCurrentWidget(editor);
        std::cout << "standard Editor setted" << std::endl;

    }
}

void MainWindow::recvEditorUpdate(int pos, QChar ch,qint32 siteId,const QTextCharFormat& format, Message::action_t action) {
    if(centralWidget->currentWidget() == editor) {
        highlightEditor->updateFromOtherEditor(pos,ch, siteId,format, action);
    }
    else{
        editor->updateFromOtherEditor(pos,ch,siteId,format, action);
    }

}
void MainWindow::fontChanged(const QFont &f)
{
    comboFont->setCurrentIndex(comboFont->findText(QFontInfo(f).family()));
    comboSize->setCurrentIndex(comboSize->findText(QString::number(f.pointSize())));
    boldAction->setChecked(f.bold());
    italicAction->setChecked(f.italic());
    underlineAction->setChecked(f.underline());
}