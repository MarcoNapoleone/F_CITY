#ifndef _USER_H
#define _USER_H

#include "auxiliary-lib/Database.h"

using namespace std;

/**
 * this is the user object aka a citizen with his UID
 * and all the biometric information.
 */
class User {
private:

    Database db;
    string name;
    string surname;
    string UID;
    int id;
    time_t birth_date;
    bool gender; /**< 0 -> female, 1 -> male */

    /**
     * This fetch all the user info from the database with the given \p id
     * @param id an unique integer number associated with the user
     */
    void fetchUserInfo(const int id);

    /**
     * This fetch all the user info from the database with the given \p IUD
     * @param UID an unique hex code associated with the user through NFC tags
     */
    void fetchUserInfo(string UID);

public:

    /**
     * constructor that fetch automatically user info from database (\p db) using \p id
     * @param db the database object the define the data source
     * @param id an unique integer number associated with the user
     */
    User(Database &db, int id);

    /**
     * constructor that fetch automatically user info from database (\p db) using \p UID
     * @param db the database object the define the data source
     * @param UID an unique hex code associated with the user through NFC tags
     */
    User(Database &db, string UID);

    User() = default;

    virtual ~User();

    void setName(const string &name);

    const Database &getDb() const;

    int getId() const;

    void setId(int id);

    void setSurname(const string &surname);

    void setBirthDate(time_t birthDate);

    void setGender(bool gender);

    void setUid(const string &uid);

};

#endif