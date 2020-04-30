#include <QApplication>
#include <QSqlDatabase>
#include <QtWidgets/QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>

#include "NetworkServer.h"
#include "database/DBSql.h"

static bool initializeDb()
{
    QSqlDatabase::addDatabase("QSQLITE");
    {
        QSqlDatabase db = QSqlDatabase::database();
        db.setDatabaseName("login.db");
        if (!db.open()) {
            QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
                                  QObject::tr("Unable to establish a database connection.\n"
                                              "This example needs SQLite support. Please read "
                                              "the Qt SQL driver documentation for information how "
                                              "to build it.\n\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
            return false;
        }
        QSqlQuery query;
        query.exec("CREATE TABLE LOGIN ("  \
         "USER      TEXT PRIMARY KEY     NOT NULL," \
         "PASS      TEXT                NOT NULL," \
         "SITEID    INT                 NOT NULL);");
        query.exec("DELETE FROM LOGIN");
        query.exec("INSERT INTO LOGIN ('USER', 'PASS', 'SITEID') VALUES ('ciao', 'suca', '5');");
        query.exec("SELECT * FROM LOGIN");

        while (query.next()) {
            QString user = query.value(0).toString();
            QString password = query.value(1).toString();
            qint32 siteId = query.value(2).toInt();
            std::cout << user.toStdString() << password.toStdString() << siteId << std::endl;
        }
    }

    {
        QSqlDatabase db = QSqlDatabase::database();
        db.setDatabaseName("ciao_directories.db");
        if (!db.open()) {
            QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
                                  QObject::tr("Unable to establish a database connection.\n"
                                              "This example needs SQLite support. Please read "
                                              "the Qt SQL driver documentation for information how "
                                              "to build it.\n\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
            return false;
        }

        QSqlQuery query;
        query.exec("CREATE TABLE DIRECTORIES ("  \
         "DIRECTORY      TEXT PRIMARY KEY     NOT NULL);");
        query.exec("DELETE FROM DIRECTORIES"); //Svuoto la tabella in caso di test multipli
        query.exec("INSERT INTO DIRECTORIES ('DIRECTORY') VALUES ('Documenti>D0');");
        query.exec("INSERT INTO DIRECTORIES ('DIRECTORY') VALUES ('Nuovo documento>F0');");
        query.exec("INSERT INTO DIRECTORIES ('DIRECTORY') VALUES ('Nuova cartella>D0');");
        query.exec("INSERT INTO DIRECTORIES ('DIRECTORY') VALUES ('Nuova cartella/file>F1');");
        query.exec("SELECT * FROM DIRECTORIES");

        while (query.next()) {
            QString name = query.value(0).toString();
            std::cout << name.toStdString() << std::endl;
        }
    db.close();
    }
    return true;
}

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    initializeDb();
    //DBSql::initialize();
    NetworkServer s;

    s.startServer();
    app.exec();
    return 0;
}