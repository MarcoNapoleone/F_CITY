//
// Created by makon on 28/01/2020.
//

#ifndef F_CITY_SHOP_H
#define F_CITY_SHOP_H

#include <string>
#include <vector>
#include <cmath>
#include "Item.h"
#include "../User.h"


using namespace std;

class Shop {
private:

    Database db;
    User user;
    string shopName;
    int shopId;
    vector<Item> items;

public:

    Shop(User &user);

    virtual ~Shop();

    void fetchShopInfo();

    void setShopName(const string &shopName);

    void fetchItems();

    const vector<Item> &getItems() const;

    const string &getShopName() const;
};

float setPrecision(float input, int precision) {

    if(input < 100000) {
        int intPart = (int) input;
        float decimalPart = input - intPart;
        decimalPart *= pow(10, precision);
        int newDecimalPart = (int) decimalPart;
        return(newDecimalPart/pow(10,precision) + intPart);
    } else return input;


}


#endif //F_CITY_SHOP_H
