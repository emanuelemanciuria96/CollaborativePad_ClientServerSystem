//
// Created by tomma on 20/04/2020.
//

#include "DBSql.h"


DBSql::DBSql(std::string name):nameDB(name){};

int callback(void *that, int argc, char **argv, char **azColName) { // Compiled SQLite Statement
    // int argc: holds the number of results
    // (array) azColName: holds each column returned
    // (array) argv: holds each value
    auto *res = (QVector<QString>*) that;

    for(int i = 0; i < argc; i++) {
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
        updateResult(cols);
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
    this->rc = sqlite3_exec(this->db, query.c_str(), callback, &this->result, &this->zErrMsg);
    std::cout<<"----------------------------------"<<std::endl;
}
void DBSql::updateResult(int cols) {
    this->result.clear();

    int result_size=sqlite3_column_bytes(this->stmt, 0); //dimensione in byte del risultato,
    if(result_size==0) { // Risultato vuoto
        return;
    }
    auto val = SQLITE_ROW;
    while(val == SQLITE_ROW){
        for (int i = 0; i < cols; i++) {
            QString key = (char *) sqlite3_column_name(this->stmt, i);
            QString val = (char *) sqlite3_column_text(this->stmt, i);
            if (this->result.find(key) == this->result.end()) {
                QVector<QString> v;
                result.insert({key, v});
            }
            this->result.at(key).push_back(val);
        }
        val = sqlite3_step(stmt);
    }
}
void DBSql::closeDB() {
    // Close the SQL connection
    sqlite3_close(this->db);
}

std::map<QString,QVector<QString>> DBSql::getResult(){
    return this->result;
}
