#ifndef _USER_H
#define _USER_H

#include "Database.h"

using namespace std;

class User {

public:

    User() = default;

    /* fetcher from db to ticket class, passing db as reference */
    void getUserInfo(Database &db, const int id);

    /* getter and setter */
    void setName(const string &name);

    void setSurname(const string &surname);

    void setBirthDate(time_t birthDate);

    const string &getName() const;

    const string &getSurname() const;

    int getRfid() const;

    time_t getBirthDate() const;

    bool getGender() const;

    void setGender(bool gender);


private:
    string name;
    string surname;
    int rfid;
    time_t birth_date;
    bool gender; //0 -> female; 1 -> male

};

#endif