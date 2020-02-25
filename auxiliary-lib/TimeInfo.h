//
// Created by makon on 15/01/2020.
//

#ifndef F_CITY_TIMEINFO_H
#define F_CITY_TIMEINFO_H

#include "time.h"
#include "../Transport/Ticket.h"

using namespace std;

/**
 * this is used to accomplish operation with time
 */
class TimeInfo {

private:

    time_t t;
    tm *timePtr;

public:

    TimeInfo();

    /**
     * used to get the date from a timestamp format
     * @return the today date
     */
    string timeDate();

    /**
     * used to get the time froma timestamp format
     * @return the instant time
     */
    string timeHour();


    tm *getTimePtr() const;

    /**
     * defining a no std operator to compare current time and ticket expiring date
     * @param ticketExpDate this is the ticket to be checked
     */
    bool operator>=(Ticket &ticketExpDate);

};

/**
 * function to convert string into unix local timestamp format
 * @param strDateTime format (yyyy-mm-dd hh:mm:ss)
 * @return unix local timestamp format
 */
time_t strToTime(const string &strDateTime);

#endif //F_CITY_TIME_H
