#include <QApplication>
#include <QSqlDatabase>
#include <QtWidgets/QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDriver>
#include <QtCore/QFile>

#include "NetworkServer.h"
#include "database/DBSql.h"

static bool initializeDb()
{
    QSqlDatabase::addDatabase("QSQLITE", "initialize");
    {
        QSqlDatabase db = QSqlDatabase::database("initialize");
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
        QSqlQuery query(db);
        query.exec("CREATE TABLE LOGIN ("  \
         "USER      TEXT PRIMARY KEY     NOT NULL," \
         "PASS      TEXT                NOT NULL," \
         "SITEID    INT                 NOT NULL);");
        query.exec("DELETE FROM LOGIN");
        query.exec("INSERT INTO LOGIN ('USER', 'PASS', 'SITEID') VALUES ('q', 'q', '1');");
        query.exec("INSERT INTO LOGIN ('USER', 'PASS', 'SITEID') VALUES ('w', 'w', '2');");
        query.exec("SELECT * FROM LOGIN");

        std::cout << "Clients in database:" << std::endl;
        std::cout << "USER" << "\t\t" << "PASS" << "\t\t" << "SITEID" << std::endl;

        while (query.next()) {
            QString user = query.value(0).toString();
            QString password = query.value(1).toString();
            qint32 siteId = query.value(2).toInt();
            std::cout << user.toStdString() << "\t\t" << password.toStdString() << "\t\t" << siteId << std::endl;
        }

        db.close();
    }

    {
        QSqlDatabase db = QSqlDatabase::database("initialize");
        db.setDatabaseName("q_directories.db");
        if (!db.open()) {
            QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
                                  QObject::tr("Unable to establish a database connection.\n"
                                              "This example needs SQLite support. Please read "
                                              "the Qt SQL driver documentation for information how "
                                              "to build it.\n\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
            return false;
        }

        QSqlQuery query(db);
        query.exec("CREATE TABLE DIRECTORIES ("  \
         "DIRECTORY      TEXT," \
         "SUBF           TEXT, PRIMARY KEY (DIRECTORY, SUBF));");
        query.exec("DELETE FROM DIRECTORIES");
        query.exec("INSERT INTO DIRECTORIES ('DIRECTORY', 'SUBF') VALUES ('', '/Cartella1>D');");
        query.exec("INSERT INTO DIRECTORIES ('DIRECTORY', 'SUBF') VALUES ('/Cartella1', '/Cartella1/Sottocartella1>D');");
        query.exec("INSERT INTO DIRECTORIES ('DIRECTORY', 'SUBF') VALUES ('/Cartella1', '/Cartella1/Sottocartella2>D');");
        query.exec("INSERT INTO DIRECTORIES ('DIRECTORY', 'SUBF') VALUES ('', '/prova>F');");
        query.exec("INSERT INTO DIRECTORIES ('DIRECTORY', 'SUBF') VALUES ('', '/Cartella2>D');");
        query.exec("SELECT * FROM DIRECTORIES");

        std::cout << "DIR" << "\t\t\t\t" << "SUBDIR" << std::endl;

        while (query.next()) {
            QString name = query.value(0).toString();
            QString sub = query.value(1).toString();
            std::cout << name.toStdString() << "\t\t\t\t" << sub.toStdString() << std::endl;
        }
        db.close();
    }

    {
        QSqlDatabase db = QSqlDatabase::database("initialize");
        db.setDatabaseName("w_directories.db");
        if (!db.open()) {
            QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
                                  QObject::tr("Unable to establish a database connection.\n"
                                              "This example needs SQLite support. Please read "
                                              "the Qt SQL driver documentation for information how "
                                              "to build it.\n\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
            return false;
        }

        QSqlQuery query(db);
        query.exec("CREATE TABLE DIRECTORIES ("  \
         "DIRECTORY      TEXT," \
         "SUBF           TEXT, PRIMARY KEY (DIRECTORY, SUBF));");
        query.exec("DELETE FROM DIRECTORIES");
        db.close();
    }

    {
        QSqlDatabase db = QSqlDatabase::database("initialize");
        db.setDatabaseName("q_files.db");
        if (!db.open()) {
            QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
                                  QObject::tr("Unable to establish a database connection.\n"
                                              "This example needs SQLite support. Please read "
                                              "the Qt SQL driver documentation for information how "
                                              "to build it.\n\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
            return false;
        }

        QSqlQuery query(db);
        query.exec("CREATE TABLE FILES ("  \
         "FILEID      TEXT PRIMARY KEY NOT NULL," \
         "DIR           TEXT NOT NULL);");
        query.exec("DELETE FROM FILES");
        query.exec("INSERT INTO FILES ('FILEID', 'DIR') VALUES ('prova2.json', '/prova2>F')");
        query.exec("INSERT INTO FILES ('FILEID', 'DIR') VALUES ('prova1.json', '/prova1>F')");
        query.exec("SELECT * FROM FILES");

        std::cout << "FILEID" << "\t\t\t\t" << "DIR" << std::endl;

        while (query.next()) {
            QString name = query.value(0).toString();
            QString sub = query.value(1).toString();
            std::cout << name.toStdString() << "\t\t\t\t" << sub.toStdString() << std::endl;
        }
        db.close();
    }

    {
        QSqlDatabase db = QSqlDatabase::database("initialize");
        db.setDatabaseName("w_files.db");
        if (!db.open()) {
            QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
                                  QObject::tr("Unable to establish a database connection.\n"
                                              "This example needs SQLite support. Please read "
                                              "the Qt SQL driver documentation for information how "
                                              "to build it.\n\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
            return false;
        }

        QSqlQuery query(db);
        query.exec("CREATE TABLE FILES ("  \
         "FILEID      TEXT PRIMARY KEY NOT NULL," \
         "DIR           TEXT NOT NULL);");
        query.exec("DELETE FROM FILES");
        query.exec("INSERT INTO FILES ('FILEID', 'DIR') VALUES ('prova2.json', '/prova2>F')");
        query.exec("INSERT INTO FILES ('FILEID', 'DIR') VALUES ('prova1.json', '/prova1>F')");
        db.close();
    }

    QSqlDatabase::removeDatabase("initialize");
    return true;
}

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    initializeDb();
    NetworkServer s;

    s.startServer();
    app.exec();
    return 0;
}