#include <QtWidgets/QApplication>
#include <thread>
#include "SharedEditor.h"
#include "LoginDialog.h"
#include <winsock2.h>
#include "EditorGUI.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    SharedEditor ed;  //connessione al server effettuata direttamente nel costruttore
    auto mainWindow = new EditorGUI(&ed);
    auto loginDialog = new LoginDialog(mainWindow);

    QObject::connect(loginDialog, &LoginDialog::acceptLogin, &ed, &SharedEditor::loginSlot);
    QObject::connect(&ed, &SharedEditor::symbolsChanged, mainWindow, &EditorGUI::updateSymbols);

    loginDialog->exec();
    mainWindow->show();              //inserisci user = ciao e password = suca se vuoi che funzioni tutto



//    QString s = "DAJEEEE";
//
//    std::cout << "Inserisci lettere:" << std::endl;
//    for(int i=0;i<s.length();i++) {
//        ed.localInsert(i, s[i]);
//    }

    app.exec();
    return 0;
}