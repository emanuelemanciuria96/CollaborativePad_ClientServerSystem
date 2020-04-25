//
// Created by tomma on 20/04/2020.
//

#ifndef SHAREDEDITORSERVER_DBSQL_H
#define SHAREDEDITORSERVER_DBSQL_H



#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <QtCore/QString>
#include <QtCore/QVector>
#include "sqlite3.h"


class DBSql {

private:
    std::string nameDB; //name of db
    sqlite3 *db; // Pointer to SQLite connection
    char *zErrMsg; // Save any error messages
    int rc; // Save the result of opening the file
    sqlite3_stmt *stmt; // Compiled SQLite Statement

    // vettore (mappa) contenente la prima riga dell'ultima query eseguita
    // vuoto se la query non è una select oppure se il risultato è nullo
    std::map<QString, QVector<QString>> result;

    void printTableResult(std::string query);
    void updateResult(int cols);
    void checkDBErrors();
public:
    DBSql(std::string name);
    void openDB();
    void query(std::string query, bool debug=0); // se debug=1 stampa la tabella risultante
    void closeDB();
    std::map<QString,QVector<QString>> getResult();
    static void initialize(){// ESEMPIO DI UTILIZZO

        // se non si indica la directory completa il db viene salvato
        // nella cartella cmake-build-debug del progetto (non so come mai)

        DBSql sqldb("login.db");
        sqldb.openDB();
        std::string query;

        query = "CREATE TABLE LOGIN ("  \
         "USER      TEXT PRIMARY KEY     NOT NULL," \
         "PASS      TEXT                NOT NULL," \
         "SITEID    INT                 NOT NULL);";
        sqldb.query(query);

        query = "DELETE FROM LOGIN"; //Svuoto la tabella in caso di test multipli
        sqldb.query(query);

        query = "INSERT INTO LOGIN ('USER', 'PASS', 'SITEID') VALUES ('ciao', 'suca', '5');";
        sqldb.query(query);

        query = "SELECT * FROM LOGIN";
        sqldb.query(query,1);//Print full table

        sqldb.closeDB();

        DBSql sqldb1("ciao_directories.db");
        sqldb1.openDB();

        query = "CREATE TABLE DIRECTORIES ("  \
         "DIRECTORY      TEXT PRIMARY KEY     NOT NULL);";
        sqldb1.query(query);

        query = "DELETE FROM DIRECTORIES"; //Svuoto la tabella in caso di test multipli
        sqldb1.query(query);

        query = "INSERT INTO DIRECTORIES ('DIRECTORY') VALUES ('/Documenti>D');";
        sqldb1.query(query);

        query = "INSERT INTO DIRECTORIES ('DIRECTORY') VALUES ('/Nuovo documento>F');";
        sqldb1.query(query);

        query = "INSERT INTO DIRECTORIES ('DIRECTORY') VALUES ('/Nuova cartella>D');";
        sqldb1.query(query);

        query = "INSERT INTO DIRECTORIES ('DIRECTORY') VALUES ('/Nuova cartella/file>F');";
        sqldb1.query(query);

        query = "SELECT * FROM DIRECTORIES";
        sqldb1.query(query,1);//Print full table

        sqldb1.closeDB();
    }// ESEMPIO DI UTILIZZO
};


#endif //SHAREDEDITORSERVER_DBSQL_H
