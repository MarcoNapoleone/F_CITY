#include "TimeInfo.h"

bool TimeInfo::operator>=(Ticket tic) {

    bool isBigger;

    isBigger = difftime(mktime(this->getTimePtr()), tic.getTicketExpDate()) >= 0;

    return (isBigger);
};


string TimeInfo::TameDate() {
    string timeDate = timePtr->tm_mday + '-' + (timePtr->tm_mon + 1) + '-' + (timePtr->tm_year + 1900);
    return (timeDate);
}

string TimeInfo::timeHour() {
    string timeHour = timePtr->tm_hour + ':' + timePtr->tm_min;
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