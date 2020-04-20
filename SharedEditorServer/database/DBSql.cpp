//
// Created by tomma on 20/04/2020.
//

#include "DBSql.h"


DBSql::DBSql(std::string name):nameDB(name){};

int callback(void *NotUsed, int argc, char **argv, char **azColName) { // Compiled SQLite Statement
    // int argc: holds the number of results
    // (array) azColName: holds each column returned
    // (array) argv: holds each value
    for(int i = 0; i < argc; i++) {
        // Show column name, value, and newline
        std::cout <<"("<< azColName[i] << ": " << argv[i]<<")  ";
    }
    // Insert a newline
    std::cout << std::endl;
    // Return successful
    return 0;
}

void DBSql::checkDBErrors() {
    if( this->rc ){
        // Show an error message
        std::cout << "DB Error: " << sqlite3_errmsg(this->db) << std::endl;
        closeDB();
    }
}

void DBSql::openDB(){
    this->rc = sqlite3_open(this->nameDB.c_str(), &this->db);
    checkDBErrors();
}

void DBSql::query(std::string query, bool debug) {
    // Run the SQL
    this->rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

    // Test it
    this->rc = sqlite3_step(this->stmt);

    // Set result if is a SELECT
    int cols = sqlite3_column_count(this->stmt);
    if(cols>0) { // if query is a SELECT
        if(debug==1) {
            printTableResult(query);
        }
        updateResult(query, cols);
    }

    // Finialize the usage
    sqlite3_finalize(this->stmt);
}

void DBSql::printTableResult(std::string query){
    int result_size=sqlite3_column_bytes(this->stmt, 0); //dimensione in byte del risultato,
    if(result_size==0) {
        std::cout << "Empty result" << std::endl;
        return;
    }
    std::cout<<"--------------RESULT--------------"<<std::endl;
    this->rc = sqlite3_exec(this->db, query.c_str(), callback, 0, &this->zErrMsg);
    std::cout<<"----------------------------------"<<std::endl;
}
void DBSql::updateResult(std::string query,int cols) {
    this->result.clear();
    int result_size=sqlite3_column_bytes(this->stmt, 0); //dimensione in byte del risultato,
    if(result_size==0) { // Risultato vuoto
        return;
    }
    for (int i = 0; i < cols; i++) {
        std::string key = (char *) sqlite3_column_name( this->stmt, i );
        std::string val = (char *) sqlite3_column_text( this->stmt, i);
        this->result.insert({key,val});
    }
}
void DBSql::closeDB() {
    // Close the SQL connection
    sqlite3_close(this->db);
}

std::map<std::string,std::string> DBSql::getResult(){
    return this->result;
}
