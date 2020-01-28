#ifndef F_CITY_TICKET_H
#define F_CITY_TICKET_H

#include "Database.h"
#include "User.h"

using namespace std;

class Ticket {
private:

    time_t ticketExpDate;
    string companyName;
    User user;
    int companyId;
    //string travelerName;
    //string travelerSurname;

public:

    /* constructor */
    Ticket(User &user);

    /* fetcher from db to ticket class, passing db as reference */
    void getTicketInfo(Database &db, const int id);

    /* setter and getter */
    void setTicketExpDate(time_t ticketExpDate);

    void setCompanyName(const string &companyName);

    void setTravelerName(const string &travelerName);

    void setTravelerSurname(const string &travelerSurname);

    time_t getTicketExpDate() const;

    const string &getCompanyName() const;

    const string &getTravelerName() const;

    const string &getTravelerSurname() const;

};

#endif //F_CITY_TICKET_H
