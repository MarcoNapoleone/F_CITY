//
// Created by makon on 28/01/2020.
//

#ifndef F_CITY_ITEM_H
#define F_CITY_ITEM_H

#include "../auxiliary-lib/Database.h"
#include "Shop.h"


class Item{

    string name;
    float price;

public:

    Item() = default;

    const string &getName() const;

    void setName(const string &name);

    float getPrice() const;

    void setPrice(float price);


};


#endif //F_CITY_ITEM_H
