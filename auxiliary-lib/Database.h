//
// Created by makon on 08/01/2020.
//

#ifndef F_CITY_DATABASE_H
#define F_CITY_DATABASE_H

/* mysql connector libraries */
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

class Database {
private:

    /* database credentials declared as members */
     string host;
     string userName;
     string pw;

public:

    /** sql var */
    sql::Driver *driver;
    sql::Connection *con;

    /* default constructor */
    // Database() = default;

    /* constructor */
    Database(const string &host, const string &userName, const string &pw);
    Database() = default;

    /* boolean method for initialization of sql var and testing if connection works */
    bool testConnection();

    /* destructor */
    virtual ~Database();

};

#endif //F_CITY_DATABASE_H
