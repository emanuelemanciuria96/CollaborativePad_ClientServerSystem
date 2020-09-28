#include <QtWidgets/QApplication>
#include <thread>
#include "SharedEditor.h"
#include "LoginDialog.h"
#include "EditorGUI.h"
#include "MainWindow.h"

int main(int argc, char **argv) {

    QApplication app(argc, argv);
    auto shEditor = new SharedEditor;  //connessione al server effettuata direttamente nel costruttore
    MainWindow mainWindow(shEditor);

    //loginDialog->exec();
    //if(loginDialog->abort)
    //    return 0;
    //shEditor->testCommand();
    //mainWindow->show();              //inserisci user = ciao e password = suca se vuoi che funzioni tutto

    mainWindow.show();
    auto returncode = app.exec();
    if (returncode == 1000)
    {
        auto* proc = new QProcess();
        proc->start(QCoreApplication::applicationFilePath());
    }
    return returncode;
}