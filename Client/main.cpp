#include <QtWidgets/QApplication>
#include <thread>
#include "SharedEditor.h"
#include "LoginDialog.h"
#include <winsock2.h>
#include "EditorGUI.h"

int main(int argc, char **argv) {

    QApplication app(argc, argv);
    auto ed = new SharedEditor;  //connessione al server effettuata direttamente nel costruttore
    auto mainWindow = new EditorGUI(ed);
    auto loginDialog = new LoginDialog(mainWindow);

    QObject::connect(loginDialog, &LoginDialog::acceptLogin, ed, &SharedEditor::loginSlot);
    QObject::connect(ed, &SharedEditor::symbolsChanged, mainWindow, &EditorGUI::updateSymbols);
    QObject::connect(ed,&SharedEditor::deleteAllText,mainWindow,&EditorGUI::deleteAllText);

    loginDialog->exec();
    if(loginDialog->abort)
        return 0;
    ed->testCommand();
    mainWindow->show();              //inserisci user = ciao e password = suca se vuoi che funzioni tutto


    app.exec();
    return 0;
}