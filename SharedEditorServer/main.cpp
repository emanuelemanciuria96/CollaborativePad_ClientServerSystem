#include <QApplication>
#include "NetworkServer.h"

int main(int argc, char **argv) {//test
    QApplication app(argc, argv);

    NetworkServer s;

    
    s.startServer();
    app.exec();
    return 0;
}
