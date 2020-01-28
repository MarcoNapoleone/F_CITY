//
// Created by makon on 28/01/2020.
//

#ifndef F_CITY_SHOP_H
#define F_CITY_SHOP_H

#include <string>
#include <list>
#include "Item.h"

using namespace std;

class Shop {
private:
    string shopName;
    int shopId;
    list <Item> products;


};


#endif //F_CITY_SHOP_H
