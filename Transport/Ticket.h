#ifndef F_CITY_TICKET_H
#define F_CITY_TICKET_H

#include "../auxiliary-lib/Database.h"
#include "../User.h"

using namespace std;

/**
 * this is the ticket that the user use to get on board on buses
 */
class Ticket {

private:

    Database db;
    User user;
    time_t ticketExpDate;
    string companyName;

    //int companyId;
    //string travelerName;
    //string travelerSurname;

public:

    /**
     * constructor
     * @param user the ticket owner
     */
    Ticket(User &user);

    /**
     * this fetch all ticket info from the database
     */
    void fetchTicketInfo();

    void setTicketExpDate(time_t ticketExpDate);

    void setCompanyName(const string &companyName);

    time_t getTicketExpDate() const;

    //void setTravelerName(const string &travelerName);

    //void setTravelerSurname(const string &travelerSurname);

    //const string &getTravelerName() const;

    //const string &getTravelerSurname() const;

};

#endif //F_CITY_TICKET_H
