//
// Created by Windows on 25/03/2020.
//




#include "EditorGUI.h"

EditorGUI::EditorGUI(QWidget *parent) : QMainWindow(parent) {
   setUpGUI();
   setWindowTitle(QCoreApplication::applicationName());
}


void EditorGUI::setUpGUI() {
//    inizializzo gli elementi
    statusBar = new QStatusBar(this);
    textEdit = new QTextEdit(this);
    toolBar = new QToolBar("ToolBar", this);

    statusBar->showMessage ("StatusBar");

//    aggiungo gli elementi alla finestra
    this->setCentralWidget(textEdit);
    this->addToolBar(toolBar);
    this->setStatusBar(statusBar);

    menuBar()->addMenu("&File");
    menuBar()->addMenu("&Options");

    textEdit->setFocus();
    setCurrentFileName(QString());

//    imposto la grandezza della finestra
    auto size = QGuiApplication::primaryScreen()->size();
    this->resize(size.width()*0.7,size.height()*0.7);
    load("./file.txt");


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

void EditorGUI::setupEditActions() {
    //TODO
}

void EditorGUI::setupFileActions() {
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