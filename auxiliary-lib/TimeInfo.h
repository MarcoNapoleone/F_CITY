//
// Created by makon on 15/01/2020.
//

#ifndef F_CITY_TIMEINFO_H
#define F_CITY_TIMEINFO_H

#include "time.h"
#include "../Transport/Ticket.h"

using namespace std;

class TimeInfo {

public:

    time_t t = time(NULL);
    tm *timePtr = localtime(&t);

    /* to print time in human friendly format */
    string timeDate();
    string timeHour();

    /* getter */
    tm *getTimePtr() const;

    /* defining a no std operator to compare current time and ticket expiring date */
    bool operator >= (Ticket ticketExpDate);

};

/* function to convert string format (yyyy-mm-dd hh:mm:ss) into unix local timestamp format */
time_t strToTime(const string &strDateTime);

#endif //F_CITY_TIME_H
