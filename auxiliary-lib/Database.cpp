#include "Database.h"
#include <iostream>

using namespace std;

/**
 * @bug this could be a cyber-security problem
 */
Database::Database(const string &host, const string &userName, const string &pw) {

    Database::host = host;
    Database::userName = userName;
    Database::pw = pw;

    driver = get_driver_instance();
    con = driver->connect(Database::host, Database::userName, Database::pw);
    con->setSchema(Database::userName);

}

bool Database::testConnection() {

    bool test;
    try {

        sql::Statement *stmt;
        sql::ResultSet *res;

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

}




