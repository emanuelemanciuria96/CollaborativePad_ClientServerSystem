#include <QApplication>
#include <QSqlDatabase>
#include <QtWidgets/QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDriver>
#include <QtCore/QFile>
#include <QtCore/QDir>

#include "NetworkServer.h"
#include "database/DBSql.h"

static bool initializeDb()
{
    QDir().mkdir("db");
    QDir().mkdir("images");
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
         "USER      TEXT PRIMARY KEY    NOT NULL," \
         "PASS      TEXT                NOT NULL," \
         "SITEID    INT                 NOT NULL,"
         "IMAGE     TEXT                NOT NULL,"
         "NAME      TEXT                NOT NULL,"
         "EMAIL     TEXT                NOT NULL);");
        query.exec("DELETE FROM LOGIN");
        query.exec("INSERT INTO LOGIN ('USER', 'PASS', 'SITEID', 'IMAGE', 'NAME', 'EMAIL') VALUES ('q', '8a5e1d339fafc39350fd8cf1d7ca7982091c27f6b77f75bd4ddab3df425b4f8c', '1', '', 'Mario Rossi', 'mario.rossi@mail.it');");
        query.exec("INSERT INTO LOGIN ('USER', 'PASS', 'SITEID', 'IMAGE', 'NAME', 'EMAIL') VALUES ('w', 'f1cfdca558ac0c00464ca0f3e265ec6fb32c57caeb106fbfed9f174f6b814642', '2', '', 'Mario Bianchi', 'mario.bianchi@mail.it');");
        query.exec("SELECT * FROM LOGIN");

        std::cout << "Clients in database:" << std::endl;
        std::cout << "USER" << "\t\t" << "PASS" << "\t\t\t\t\t\t\t\t\t\t" << "SITEID" << std::endl;

        while (query.next()) {
            QString user = query.value(0).toString();
            QString password = query.value(1).toString();
            qint32 siteId = query.value(2).toInt();
            std::cout << user.toStdString() << "\t\t" << password.toStdString() << "\t\t" << siteId << std::endl;
        }
        std::cout << std::endl;
        db.close();
    }

    std::cout << "----------TABELLE VECCHIE----------" << std::endl;

    {
        QSqlDatabase db = QSqlDatabase::database("initialize");
        db.setDatabaseName("directories.db");
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
         "SITEID         INT," \
         "DIRECTORY      TEXT," \
         "SUBF           TEXT, PRIMARY KEY (SITEID, DIRECTORY, SUBF));");
        query.exec("DELETE FROM DIRECTORIES");
        query.exec("INSERT INTO DIRECTORIES ('SITEID', 'DIRECTORY', 'SUBF') VALUES ('1', '', '/Cartella1>D');");
        query.exec("INSERT INTO DIRECTORIES ('SITEID', 'DIRECTORY', 'SUBF') VALUES ('1', '/Cartella1', '/Cartella1/Sottocartella1>D');");
        query.exec("INSERT INTO DIRECTORIES ('SITEID', 'DIRECTORY', 'SUBF') VALUES ('1', '/Cartella1', '/Cartella1/Sottocartella2>D');");
        query.exec("INSERT INTO DIRECTORIES ('SITEID', 'DIRECTORY', 'SUBF') VALUES ('1', '', '/prova1>F');");
        query.exec("INSERT INTO DIRECTORIES ('SITEID', 'DIRECTORY', 'SUBF') VALUES ('1', '', '/prova2>F');");
        query.exec("INSERT INTO DIRECTORIES ('SITEID', 'DIRECTORY', 'SUBF') VALUES ('1', '', '/Cartella2>D');");
        query.exec("INSERT INTO DIRECTORIES ('SITEID', 'DIRECTORY', 'SUBF') VALUES ('2', '', '/prova1>F');");
        query.exec("INSERT INTO DIRECTORIES ('SITEID', 'DIRECTORY', 'SUBF') VALUES ('2', '', '/prova2>F');");
        query.exec("SELECT * FROM DIRECTORIES");

        std::cout << "SITEID" << "\t\t\t\t" << "DIR" << "\t\t\t\t" << "SUBDIR" << std::endl;

        while (query.next()) {
            qint32 siteId = query.value(0).toInt();
            QString name = query.value(1).toString();
            QString sub = query.value(2).toString();
            std::cout << siteId << "\t\t\t\t" << name.toStdString() << "\t\t\t\t" << sub.toStdString() << std::endl;
        }
        std::cout << std::endl;
        db.close();
    }

    {
        QSqlDatabase db = QSqlDatabase::database("initialize");
        db.setDatabaseName("files.db");
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
         "SITEID      INT," \
         "FILEID      TEXT NOT NULL," \
         "DIR         TEXT NOT NULL, PRIMARY KEY (SITEID, FILEID));");
        query.exec("DELETE FROM FILES");
        query.exec("INSERT INTO FILES ('SITEID', 'FILEID', 'DIR') VALUES ('1', 'prova1.json', '/prova1>F');");
        query.exec("INSERT INTO FILES ('SITEID', 'FILEID', 'DIR') VALUES ('1', 'prova2.json', '/prova2>F');");
        query.exec("INSERT INTO FILES ('SITEID', 'FILEID', 'DIR') VALUES ('2', 'prova1.json', '/prova1>F');");
        query.exec("INSERT INTO FILES ('SITEID', 'FILEID', 'DIR') VALUES ('2', 'prova2.json', '/prova2>F');");
        query.exec("SELECT * FROM FILES");

        std::cout << "SITEID" << "\t\t\t\t" << "FILEID" << "\t\t\t\t\t" << "DIR" << std::endl;

        while (query.next()) {
            qint32 siteId = query.value(0).toInt();
            QString name = query.value(1).toString();
            QString sub = query.value(2).toString();
            std::cout << siteId << "\t\t\t\t" << name.toStdString() << "\t\t\t\t" << sub.toStdString() << std::endl;
        }
        std::cout << std::endl;
        db.close();
    }
    std::cout << "----------------------------------" << std::endl;
    std::cout << "----------TABELLE NUOVE----------" << std::endl;

    {
        QSqlDatabase db = QSqlDatabase::database("initialize");
        db.setDatabaseName("db/files.db");
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
         "SITEID         INT," \
         "NAME           TEXT," \
         "OWNER          TEXT," \
         "FSNAME         TEXT, PRIMARY KEY (SITEID, NAME, OWNER));");
        query.exec("DELETE FROM FILES");
        query.exec("INSERT INTO FILES ('SITEID', 'NAME', 'OWNER', 'FSNAME') VALUES ('1', 'prova1', '#', 'prova1.json');");
        query.exec("INSERT INTO FILES ('SITEID', 'NAME', 'OWNER', 'FSNAME') VALUES ('1', 'prova2', '#', 'prova2.json');");
        query.exec("INSERT INTO FILES ('SITEID', 'NAME', 'OWNER', 'FSNAME') VALUES ('2', 'prova1', 'q', 'prova1.json');");
        query.exec("INSERT INTO FILES ('SITEID', 'NAME', 'OWNER', 'FSNAME') VALUES ('2', 'prova2', 'q', 'prova2.json');");
        query.exec("SELECT * FROM FILES");

        std::cout << "SITEID" << "\t\t\t\t" << "NAME" << "\t\t\t\t" << "OWNER" << "\t\t\t\t" << "FSNAME" << std::endl;

        while (query.next()) {
            qint32 siteId = query.value(0).toInt();
            QString name = query.value(1).toString();
            QString owner = query.value(2).toString();
            QString fsname = query.value(3).toString();
            std::cout << siteId << "\t\t\t\t" << name.toStdString() << "\t\t\t\t" << owner.toStdString() << "\t\t\t\t" << fsname.toStdString() << std::endl;
        }
        std::cout << std::endl;
        db.close();
    }

    std::cout << "---------------------------------" << std::endl;
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