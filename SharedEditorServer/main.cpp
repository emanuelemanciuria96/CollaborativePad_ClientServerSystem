#include <QApplication>
#include "NetworkServer.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    NetworkServer s;   //il server accetta la connessione di un solo client e simula il comportamento di un secondo clie
                        // con siteId=1 alla ricezione di 'c' e 'a' da parte del client (infatti implementa quasi tutte le funzioni di un client)

    int i = 0;
    for(;i<5;i++)
        std::cout<<"diocane fai il commit!!!";
    s.startServer();
    app.exec();
    return 0;
}