//
// Created by tomma on 20/04/2020.
//

#ifndef SHAREDEDITORSERVER_DBSQL_H
#define SHAREDEDITORSERVER_DBSQL_H



#include <string>
#include <iostream>
#include <map>
#include <vector>
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
    std::map<std::string, std::string> result;


    void printTableResult(std::string query);
    void updateResult(int cols);
    void checkDBErrors();
public:
    DBSql(std::string name);
    void openDB();
    void query(std::string query, bool debug=0); // se debug=1 stampa la tabella risultante
    void closeDB();
    std::map<std::string,std::string> getResult();

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

        query = "DELETE FROM PEOPLE"; //Svuoto la tabella in caso di test multipli
        sqldb.query(query);

        query = "INSERT INTO LOGIN ('USER', 'PASS', 'SITEID') VALUES ('ciao', 'suca', '5');";
        sqldb.query(query);

        query = "SELECT * FROM LOGIN";
        sqldb.query(query,1);//Print full table

        query = "SELECT PASS FROM LOGIN WHERE USER='ciao'";
        sqldb.query(query);

        sqldb.closeDB();
    }// ESEMPIO DI UTILIZZO
};


#endif //SHAREDEDITORSERVER_DBSQL_H
