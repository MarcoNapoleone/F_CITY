//
// Created by makon on 28/01/2020.
//

#ifndef F_CITY_SHOP_H
#define F_CITY_SHOP_H

#include <string>
#include <vector>
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


#endif //F_CITY_SHOP_H
