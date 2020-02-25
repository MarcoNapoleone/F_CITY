#ifndef F_CITY_ITEM_H
#define F_CITY_ITEM_H

#include "../auxiliary-lib/Database.h"

/**
 * this is an item that represents a shop product
 */
class Item {

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
