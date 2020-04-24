//
// Created by Windows on 25/03/2020.
//

#include "EditorGUI.h"

EditorGUI::EditorGUI(SharedEditor *model, QWidget *parent) : QMainWindow(parent){
    signalBlocker = false;
    setModel(model);
    setUpGUI();
    setWindowTitle(QCoreApplication::applicationName());
}


void EditorGUI::setUpGUI() {
//    inizializzo gli elementi
    statusBar = new QStatusBar(this);
    textEdit = new QTextEdit(this);
    toolBar = new QToolBar("Toolbar",this);

    statusBar->showMessage ("StatusBar");

//    aggiungo gli elementi alla finestra
    this->setCentralWidget(textEdit);
    this->setStatusBar(statusBar);
    this->addToolBar(toolBar);
    toolBar->setMovable(false);

    setupFileActions();
    menuBar()->addMenu("&Options");

    textEdit->setFocus();
    setCurrentFileName(QString());

//    imposto la grandezza della finestra
    auto size = QGuiApplication::primaryScreen()->size();
    this->resize(size.width()*0.7,size.height()*0.7);

    connect(textEdit->document(), SIGNAL(contentsChange(int, int, int)), this, SLOT(contentsChange(int,int,int)));

//    load("./file.txt");
    loadSymbols();

}


bool EditorGUI::load(const QString &f) {
    QString f1 = R"(C:\Users\Windows\Documents\POLITO\Programmazione di sistema\Progetto\MyTest\file.txt)";
    if(!QFile::exists(f1)){
        std::cout << "File non esiste";
        return false;
    }
    QFile file(f1);

    if(!file.open(QFile::ReadOnly)) {
        std::cout << "File non aperto";
        return false;
    }

    QTextStream in(&file);
    QString str = in.readAll();
//    QByteArray data = file.readAll();
//    QTextCodec *codec = Qt::codecForHtml(data);
//    QString str = codec->toUnicode(data);
//    textEdit->setPlainText(QString::fromUtf8(data));
    textEdit->setPlainText(str);
    setCurrentFileName(f);
    return true;
}


void EditorGUI::loadSymbols() {
    signalBlocker = !signalBlocker;
    textEdit->setText(model->to_string());
    signalBlocker = !signalBlocker;
}

void EditorGUI::setupFileActions() {
//    QToolBar *tb = addToolBar(tr("File Actions"));
    QMenu *menu = menuBar()->addMenu(tr("&File"));

    QAction *a = menu->addAction(tr("&New"),this,&EditorGUI::fileNew);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::New);
//    tb->addAction(a);

    a = menu->addAction(tr("&Open..."), this, &EditorGUI::fileOpen);
    a->setShortcut(QKeySequence::Open);
//    tb->addAction(a);

    menu->addSeparator();

    actionSave = menu->addAction(tr("&Save"), this, &EditorGUI::fileSave);
    actionSave->setShortcut(QKeySequence::Save);
    actionSave->setEnabled(false);
//    tb->addAction(actionSave);

    a = menu->addAction(tr("Save &As..."), this, &EditorGUI::fileSaveAs);
    a->setPriority(QAction::LowPriority);
    menu->addSeparator();

    a = menu->addAction(tr("&Quit"), this, &EditorGUI::close);
    a->setShortcut(Qt::CTRL + Qt::Key_Q);

}

void EditorGUI::setupEditActions() {
    //TODO
}

void EditorGUI::setupTextActions() {
    //TODO
}

void EditorGUI::setCurrentFileName(const QString &filename) {
    this->fileName = filename;
    textEdit->document()->setModified(false);

    QString showName;
    if(fileName.isEmpty())
        showName = "untitled.txt";
    else
        showName = QFileInfo(fileName).fileName();

    setWindowTitle(showName + " - " + QCoreApplication::applicationName());
    setWindowModified(false);
}

void EditorGUI::setModel(SharedEditor* _model) {
    this->model = _model;
}

void EditorGUI::contentsChange(int pos, int charsRemoved, int charsAdded) {
    int i=0;
    if(!signalBlocker) {
        if (charsRemoved > 0) {  //sono stati cancellati dei caratteri
            std::cout << "Cancellazione carattere " << pos << std::endl;
            for (i = 0; i < charsRemoved; i++) {
                model->localErase(pos + i);
            }
        }
        if (charsAdded > 0) {  //sono stati aggiunti caratteri
            std::cout << "Inserimento carattere " << pos << std::endl;
            for (i = 0; i < charsAdded; i++) {
                model->localInsert(pos + i, textEdit->document()->characterAt(pos + i));
            }
        }
    }
}

void EditorGUI::insertText(qint32 pos, QChar value) {
    pos--;
    auto cursor = textEdit->textCursor();
//    cursor.movePosition(QTextCursor::MoveOperation::Start, QTextCursor::MoveMode::MoveAnchor,1);
//    cursor.movePosition(QTextCursor::MoveOperation::NextCharacter, QTextCursor::MoveMode::MoveAnchor,pos);
    cursor.setPosition(pos,QTextCursor::MoveMode::MoveAnchor);
    signalBlocker = !signalBlocker;
    cursor.insertText(QString(value));
    std::cout << "Inserito " << pos << " " << value.unicode() << std::endl;
    signalBlocker = !signalBlocker;
}

void EditorGUI::deleteText(qint32 pos) {
    pos--;
    auto cursor = textEdit->textCursor();
//    cursor.movePosition(QTextCursor::MoveOperation::Start, QTextCursor::MoveMode::MoveAnchor,1);
//    cursor.movePosition(QTextCursor::MoveOperation::NextCharacter, QTextCursor::MoveMode::MoveAnchor,pos);
    cursor.setPosition(pos,QTextCursor::MoveMode::MoveAnchor);
    signalBlocker = !signalBlocker;
    cursor.deleteChar();
    std::cout << "Rimosso " << pos << std::endl;
    signalBlocker = !signalBlocker;
}


void EditorGUI::updateSymbols(qint32 pos, QChar value, const QString& action) {
    if(action == "remove")
        deleteText(pos);
    else
        insertText(pos,value);
}

void EditorGUI::updateRemoteCursor(qint32 siteId, int pos) {
    if (remoteCursors[siteId].isNull()) {
        remoteCursors[siteId].setPosition(pos,QTextCursor::MoveMode::MoveAnchor);
    } else
        remoteCursors.emplace(remoteCursors.begin()+siteId, siteId, pos);
}

void EditorGUI::removeCursor(qint32 siteId) {
    if (!remoteCursors[siteId].isNull()){

        remoteCursors.erase(remoteCursors.begin()+siteId);
    }
}

void EditorGUI::fileNew() {
//    TODO
}

void EditorGUI::fileOpen() {
//    TODO
}

void EditorGUI::fileSave() {
//    TODO
}

void EditorGUI::fileSaveAs() {
//    TODO
}