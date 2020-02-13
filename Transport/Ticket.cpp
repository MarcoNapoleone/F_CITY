#include "Ticket.h"
#include "../auxiliary-lib/TimeInfo.h"


Ticket::Ticket(User &user){
    this->user = user;
    this->db = user.getDb();
    this->fetchTicketInfo();
}

void Ticket::fetchTicketInfo() {

    /* checking connection */
    if (db.testConnection()) {

        try {

            sql::ResultSet *res;
            sql::PreparedStatement *pstmt; //using prepared statement

            pstmt = db.con->prepareStatement("SELECT * FROM tickets WHERE id = ?"); //sql injection
            pstmt->setInt(1, this->user.getId()); //replace '?' with [int]id
            res = pstmt->executeQuery();

            while (res->next()) {

                //this->setTravelerName(res->getString("traveler_name"));
                //this->setTravelerSurname(res->getString("traveler_surname"));
                this->setCompanyName(res->getString("company_name"));

                /* turn time from string format (yyyy-mm-dd hh:mm:ss) into unix local timestamp format */
                this->setTicketExpDate(strToTime((string) res->getString("bus_pass_exp_date"))); //casting from sql::string to std::string

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


void Ticket::setTicketExpDate(time_t ticketExpDate) {
    Ticket::ticketExpDate = ticketExpDate;
}

void Ticket::setCompanyName(const string &companyName) {
    Ticket::companyName = companyName;
}

/*void Ticket::setTravelerName(const string &travelerName) {
    Ticket::travelerName = travelerName;
}*/

/*void Ticket::setTravelerSurname(const string &travelerSurname) {
    Ticket::travelerSurname = travelerSurname;
}*/

time_t Ticket::getTicketExpDate() const {
    return ticketExpDate;
}

const string &Ticket::getCompanyName() const {
    return companyName;
}

/*const string &Ticket::getTravelerName() const {
    return travelerName;
}

const string &Ticket::getTravelerSurname() const {
    return travelerSurname;
}*/
