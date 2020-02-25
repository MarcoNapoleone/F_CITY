//
// Created by makon on 08/01/2020.
//

#ifndef F_CITY_DATABASE_H
#define F_CITY_DATABASE_H

/**
 * @include mysql connector libraries
 */
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

/**
 * this is the main data source that help to fetch all information
 * once created will be passed as reference to all others server based object constructors
 */
class Database {

private:

    string host;
    string userName;
    string pw;

public:

    /**
     * sql var
     */
    sql::Driver *driver;
    sql::Connection *con;

    /**
     * constructor
     * @param host the IP address
     * @param userName the username credential
     * @param pw the password
     */
    Database(const string &host, const string &userName, const string &pw);

    Database() = default;

    /**
     * this is used to check the connection
     * @return 1 if the connection is online
     */
    bool testConnection();

    virtual ~Database();

};

#endif //F_CITY_DATABASE_H
