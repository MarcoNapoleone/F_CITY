
#ifndef F_CITY_BANK_H
#define F_CITY_BANK_H

#include "User.h"

class Bank : User {
private:
    User user;

public:
    Bank(User &user);

};


#endif //F_CITY_BANK_H
