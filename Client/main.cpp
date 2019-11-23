#include <QtWidgets/QApplication>
#include <thread>
#include "SharedEditor.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    SharedEditor ed;  //connessione al server effettuata direttamente nel costruttore

    int i=0;
    char ch;
    for(;i<5;i++) {
        std::cin>>ch;
        ed.localInsert(i, ch);         //invia i caratteri 'c' e 'a', dal server riceve 't' e 'h' e cancella la 'c'
    }                                               //ogni volta che c'è inserimento, cancellazione, ricezione di Message stampa
                                                    //la stringa

    app.exec();
    return 0;
}