#include "TimeInfo.h"

bool TimeInfo::operator>=(Ticket tic) {

    bool isBigger;

    isBigger = difftime(mktime(this->getTimePtr()), tic.getTicketExpDate()) >= 0;

    return (isBigger);
};


string TimeInfo::timeDate() {
    string timeDate = to_string(timePtr->tm_mday) + "-" + to_string(timePtr->tm_mon + 1) + "-" +
                      to_string(timePtr->tm_year - 100);
    return (timeDate);
}

string TimeInfo::timeHour() {
    string timeHour = to_string(timePtr->tm_hour) + "-" + to_string(timePtr->tm_min);
    return (timeHour);
}

tm *TimeInfo::getTimePtr() const {
    return timePtr;
}

time_t strToTime(const string &strDateTime) {
    tm t;
    strptime(strDateTime.c_str(), "%F %T", &t);
    return mktime(&t);
}