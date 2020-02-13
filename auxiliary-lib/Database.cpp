#include "Database.h"
#include <iostream>

using namespace std;

Database::Database(const string &host, const string &userName, const string &pw) {

    Database::host = host;
    Database::userName = userName;
    Database::pw = pw;
}

bool Database::testConnection() {

    bool test = 0;
    try {

        sql::Statement *stmt;
        sql::ResultSet *res;

        /* checking if connection is successful */
        driver = get_driver_instance();
        con = driver->connect(Database::host, Database::userName, Database::pw);
        con->setSchema(Database::userName);
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT '1' AS _message"); //return 1 in any case
        res->next();
        test = stoi(res->getString("_message")); //reading the column

        delete stmt;
        delete res;


    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;  //exceptions for connection errors
    }
    return (test); // 1 = connection established, 0 = viceversa
}

Database::~Database() {
    delete con;
}




