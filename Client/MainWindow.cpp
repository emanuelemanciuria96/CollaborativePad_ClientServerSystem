//
// Created by utente on 06/08/2020.
//

#include <QtWidgets/QGroupBox>
#include "MainWindow.h"


MainWindow::MainWindow(SharedEditor* shEditor, QWidget *parent) : QMainWindow(parent) {
    QApplication::setStyle(QStyleFactory::create("fusion"));
//    for(auto k : QStyleFactory::keys()){
//        std::cout << k.toStdString() << std::endl;
//    }
    setWindowTitle("Shared Editor");
    statusBar = new QStatusBar(this);
    statusBar->showMessage ("StatusBar");
    toolBar = new QToolBar("Toolbar",this);
    centralWidget = new QStackedWidget(this);

    //    aggiungo gli elementi alla finestra
    this->setStatusBar(statusBar);
    this->addToolBar(toolBar);
    toolBar->setMovable(false);
    setCentralWidget(centralWidget);

    menuBar()->addMenu("&Options");

    // login creation
    loginSettings();
    // editor creation
    editorSettings(shEditor);
    // tree file system view creation
    treeFileSystemSettings();
    // widgetAccount creation
    infoWidgetsSettings();

    connect(loginDialog, &LoginDialog::acceptLogin, shEditor, &SharedEditor::loginSlot);
    connect(treeView, &FileSystemTreeView::opnFileRequest,shEditor , &SharedEditor::requireFile);
    connect(treeView, &FileSystemTreeView::renFileRequest,shEditor , &SharedEditor::requireFileRename);
    connect(shEditor, &SharedEditor::fileNameEdited, treeView, &FileSystemTreeView::editFileName);
    connect(shEditor, &SharedEditor::loginAchieved, this, &MainWindow::loginFinished);
    connect(shEditor, &SharedEditor::symbolsChanged, editor, &EditorGUI::updateSymbols);
    connect(shEditor,&SharedEditor::deleteAllText, editor,&EditorGUI::deleteAllText);
    connect(shEditor, &SharedEditor::remoteCursorPosChanged, editor, &EditorGUI::updateRemoteCursorPos);
    connect(shEditor, &SharedEditor::removeCursor, editor, &EditorGUI::removeCursor);
    connect(shEditor, &SharedEditor::deleteAllText, editor, &EditorGUI::deleteAllText);
    connect(shEditor, &SharedEditor::filePathsArrived, treeView, &FileSystemTreeView::constructFromPaths);
    connect(this, &MainWindow::fileSystemRequest, shEditor, &SharedEditor::requireFileSystem);
    connect(shEditor, &SharedEditor::userInfoArrived, infoWidget, &InfoWidget::loadData);
    connect(infoWidget, &InfoWidget::sendUpdatedInfo, shEditor, &SharedEditor::sendUpdatedInfo);
    connect(loginDialog, &LoginDialog::signIn, this, &MainWindow::startSignIn);
    connect(infoWidgetEdit, &InfoWidgetEdit::backToLogIn, this, &MainWindow::backToLogIn);

    //    imposto la grandezza della finestra
    auto size = QGuiApplication::primaryScreen()->size();
    this->resize(size.width()*0.7,size.height()*0.7);

    centralWidget->addWidget(widgetLogin);
    centralWidget->addWidget(widgetInfoEditC);
    centralWidget->addWidget(widgetEditor);
//    this->setCentralWidget(widgetLogin);

}

void MainWindow::loginFinished() {
    widgetLogin->hide();
    emit fileSystemRequest();
    centralWidget->setCurrentWidget(widgetEditor);
    dockWidgetTree->show();
    widgetEditor->show();
}

void MainWindow::loginSettings() {

    widgetLogin = new QWidget(this);

    QPalette p1{};
    QImage loginBackground = QImage("./textures/texture_clouds_background.png");
    QBrush brush1(loginBackground);
    p1.setBrush(QPalette::Window,brush1);
    widgetLogin->setAutoFillBackground(true);
    widgetLogin->setPalette(p1);
    widgetLogin->setLayout( new QGridLayout(widgetLogin) );

    QGroupBox *boxLogin = new QGroupBox(widgetLogin);
    loginDialog = new LoginDialog(boxLogin);
    boxLogin->setLayout(new QVBoxLayout());

    // pinting box
    QRgb rgbColor = loginBackground.pixel(0,0);

    QPalette p2{};
    QLinearGradient grad(0,50,0,0);
    grad.setColorAt(0,QColor(rgbColor));
    grad.setColorAt(1,Qt::lightGray);
    QBrush brush2(grad);
    p2.setBrush(QPalette::Window,brush2);
    boxLogin->setAutoFillBackground(true);
    boxLogin->setPalette(p2);

    /*boxLogin->setStyleSheet("QGroupBox {border: 0px;"
                            "border-radius: 15px;"
                            "margin-top: 1ex;}");
                            */
    boxLogin->setTitle("login");
    //boxLogin->layout()->addWidget(new QLabel("Please insert your user and password in the following boxes",widgetLogin));
    boxLogin->layout()->addWidget(loginDialog);

    dynamic_cast<QGridLayout*>(widgetLogin->layout())->addWidget(boxLogin,1,1,4,1,Qt::AlignCenter);

}


void MainWindow::treeFileSystemSettings() {
    dockWidgetTree = new QDockWidget(tr("files"),this);
    dockWidgetTree->setAllowedAreas(Qt::LeftDockWidgetArea );
    this->setAnimated(QMainWindow::AnimatedDocks);
    treeView = new FileSystemTreeView(dockWidgetTree);
    dockWidgetTree->setWidget(treeView);

    this->addDockWidget(Qt::LeftDockWidgetArea,dockWidgetTree);
    dockWidgetTree->hide();
}


void MainWindow::editorSettings(SharedEditor* shEditor) {
    widgetEditor = new QWidget(this);
    widgetEditor->setStyleSheet("QWidget { background: lightGray; }");
    editor = new EditorGUI(shEditor, widgetEditor);
    editor->setStyleSheet("QWidget { background: white; }");
    auto layoutEditor = new QVBoxLayout(widgetEditor);
    layoutEditor->addWidget(editor);
    layoutEditor->setContentsMargins(100,0,100,0);

    widgetEditor->hide();

}

void MainWindow::startSignIn() {
    centralWidget->setCurrentWidget(widgetInfoEditC);
    widgetInfoEditC->show();
    infoWidgetEdit->show();
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
    centralWidget->setCurrentWidget(widgetLogin);
}
