#include <QApplication>
#include "NetworkServer.h"
#include "database/DBSql.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    DBSql::initialize();
    NetworkServer s;


    s.startServer();
    app.exec();

    return 0;
}