//
// Created by makon on 28/01/2020.
//

#include "Shop.h"
#include <time.h>

Shop::Shop(User &user){

    this->user = user;
    this->db = user.getDb();
    this->fetchShopInfo();
    this->fetchItems();
    this->shopId = user.getId();
}

void Shop::fetchShopInfo(){

    /* checking connection */
    if (db.testConnection()) {

        try {

            sql::ResultSet *res;
            sql::PreparedStatement *pstmt; //using prepared statement

            pstmt = db.con->prepareStatement("SELECT name FROM shops WHERE user_id = ?"); //sql injection
            pstmt->setInt(1, user.getId());
            res = pstmt->executeQuery();

            while (res->next()) {

                this->setShopName(res->getString("name"));

            }
            delete res;
            delete pstmt;

        }
        catch (sql::SQLException &e) {
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        }
    } else cout << "connection error!";

}

void Shop::setShopName(const string &shopName) {
    Shop::shopName = shopName;
}

void Shop::fetchItems(){

    /* checking connection */
    if (db.testConnection()) {

        try {

            sql::ResultSet *res;
            sql::PreparedStatement *pstmt; //using prepared statement

            pstmt = db.con->prepareStatement("SELECT * FROM items WHERE shop_id = ?"); //sql injection
            pstmt->setInt(1, this->shopId);
            res = pstmt->executeQuery();

            Item itemTemp;
            while (res->next()) {
                itemTemp.setPrice(res->getDouble("price"));
                itemTemp.setName(res->getString("name"));
                this->items.push_back(itemTemp);
            }
            delete res;
            delete pstmt;

        }
        catch (sql::SQLException &e) {
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        }
    } else cout << "connection error!";



}

const vector<Item> &Shop::getItems() const {
    return items;
}

Shop::~Shop() {

    delete(&items);

}
