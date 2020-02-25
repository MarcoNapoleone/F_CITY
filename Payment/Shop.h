#ifndef F_CITY_SHOP_H
#define F_CITY_SHOP_H

#include <string>
#include <vector>
#include "Item.h"
#include "../User.h"


using namespace std;

/**
 * this is the shop owned by the user
 */
class Shop {

private:

    Database db;
    User user;
    string shopName;
    int shopId;
    vector<Item> items; /** vector of items */

    /**
     * used to get all the items of the seller
     */
    void fetchItems();

    /**
     * this fetch all the shop info from the database
     */
    void fetchShopInfo();

public:

    /**
     * constructor
     * @param user the owner
     */
    Shop(User &user);

    virtual ~Shop();

    void setShopName(const string &shopName);

    const vector<Item> &getItems() const;

};


#endif //F_CITY_SHOP_H
