#include "TimeInfo.h"

bool TimeInfo::operator>=(Ticket &ticketExpDate) {

    bool isBigger;

    isBigger = difftime(mktime(this->getTimePtr()), ticketExpDate.getTicketExpDate()) >= 0;

    return (isBigger);
};


string TimeInfo::timeDate() {
    string timeDate = to_string(timePtr->tm_year - 100) + "-" + to_string(timePtr->tm_mon + 1) + "-" +
                      to_string(timePtr->tm_mday);
    return (timeDate);
}

string TimeInfo::timeHour() {
    string timeHour = to_string(timePtr->tm_hour) + "-" + to_string(timePtr->tm_min) + "-" + to_string(timePtr->tm_sec);
    return (timeHour);
}

tm *TimeInfo::getTimePtr() const {
    return timePtr;
}

TimeInfo::TimeInfo() {
    t = time(NULL);
    timePtr = localtime(&t);
}

time_t strToTime(const string &strDateTime) {
    tm t;
    strptime(strDateTime.c_str(), "%F %T", &t);
    return mktime(&t);
}