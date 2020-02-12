//
// Created by makon on 10/02/2020.
//

#ifndef F_CITY_RC522_H
#define F_CITY_RC522_H


#include <string>
#include "Hardware.h"

class Rc522 : public Hardware {

    std::string uid;

public:
    Rc522() = default;
    std::string readTag();
};


#endif //F_CITY_RC522_H
