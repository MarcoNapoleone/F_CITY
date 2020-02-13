#include "User.h"
#include "auxiliary-lib/TimeInfo.h"

User::User(Database &db, int id){
    this->db = db;
    this->fetchUserInfo(id);
}

User::User(Database &db, string UID){
    this->db = db;
    this->fetchUserInfo(UID);
}

void User::fetchUserInfo(const int id) {

    /* checking connection */
    if (this->db.testConnection()) {

        try {

            sql::ResultSet *res;
            sql::PreparedStatement *pstmt; //using prepared statement

            pstmt = db.con->prepareStatement("SELECT * FROM users WHERE id = ?"); //sql injection
            pstmt->setInt(1, id); //replace '?' with [int]id
            res = pstmt->executeQuery();

            while (res->next()) {

                this->setName(res->getString("name"));
                this->setSurname(res->getString("surname"));
                this->setGender(res->getBoolean("gender"));

                /* turn time from string format (yyyy-mm-dd hh:mm:ss) into unix local timestamp format */
                this->setBirthDate(strToTime((string) res->getString("birthday")));

            }
            delete res;
            delete pstmt;

        }
        catch (sql::SQLException &e) {
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        }
    } else cout << "connection error!";

}


void User::fetchUserInfo(string UID) {

    /* checking connection */
    if (this->db.testConnection()) {

        try {

            sql::ResultSet *res;
            sql::PreparedStatement *pstmt; //using prepared statement

            pstmt = db.con->prepareStatement("SELECT * FROM users WHERE UID = ?"); //sql injection
            pstmt->setString(1, UID); //replace '?'
            res = pstmt->executeQuery();

            while (res->next()) {

                this->setName(res->getString("name"));
                this->setSurname(res->getString("surname"));
                this->setGender(res->getBoolean("gender"));

                /* turn time from string format (yyyy-mm-dd hh:mm:ss) into unix local timestamp format */
                this->setBirthDate(strToTime((string) res->getString("birthday")));

            }
            delete res;
            delete pstmt;

        }
        catch (sql::SQLException &e) {
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        }
    } else cout << "connection error!";

}


void User::setName(const string &name) {
    User::name = name;
}

void User::setSurname(const string &surname) {
    User::surname = surname;
}

void User::setBirthDate(time_t birthDate) {
    birth_date = birthDate;
}

void User::setGender(bool gender) {
    User::gender = gender;
}

const string &User::getName() const {
    return name;
}

const string &User::getSurname() const {
    return surname;
}

int User::getRfid() const {
    return rfid;
}

time_t User::getBirthDate() const {
    return birth_date;
}

bool User::getGender() const {
    return gender;
}

int User::getId() const {
    return id;
}

void User::setId(int id) {
    User::id = id;
}

const Database &User::getDb() const {
    return db;
}

User::~User() {


}
