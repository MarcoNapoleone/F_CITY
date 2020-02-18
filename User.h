#ifndef _USER_H
#define _USER_H

#include "auxiliary-lib/Database.h"

using namespace std;

class User {
private:

    Database db;
    string name;
    string surname;
    string UID;
    int id;
    time_t birth_date;
    bool gender; //0 -> female; 1 -> male

    /* fetcher from db to ticket class, passing db as reference */
    void fetchUserInfo(const int id);
    void fetchUserInfo(string UID);

public:

    User(Database &db, int id);

    User(Database &db, string UID);

    User() = default;

    virtual ~User();


    /* getter and setter */
    void setName(const string &name);

    const Database &getDb() const;

    int getId() const;

    void setId(int id);

    void setSurname(const string &surname);

    void setBirthDate(time_t birthDate);

    const string &getName() const;

    const string &getSurname() const;

    string getUID() const;

    time_t getBirthDate() const;

    bool getGender() const;

    void setGender(bool gender);

    void setUid(const string &uid);

};

#endif