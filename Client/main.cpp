#include <QtWidgets/QApplication>
#include <thread>
#include "SharedEditor.h"
#include "LoginDialog.h"
#include <QMainWindow>
#include <winsock2.h>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    auto loginDialog = new LoginDialog(&mainWindow);

    SharedEditor ed;  //connessione al server effettuata direttamente nel costruttore

    QObject::connect(loginDialog, &LoginDialog::acceptLogin, &ed, &SharedEditor::login);
    mainWindow.show();              //inserisci user = ciao e password = suca se vuoi che funzioni tutto
    loginDialog->exec();

    int i=0;
    char ch;

    std::cout << "Inserisci lettere:" << std::endl;
    for(;i<5;i++) {
        std::cin>>ch;
        ed.localInsert(i, ch);
    }

    app.exec();
    return 0;
}