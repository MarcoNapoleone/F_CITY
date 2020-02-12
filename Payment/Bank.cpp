//
// Created by makon on 07/01/2020.
//

#include "Bank.h"
#include "Item.h"

Bank::Bank(User &user) {

    this->user = user;
    this->db = user.getDb();
    this->fetchBalanceInfo();

}

void Bank::fetchBalanceInfo() {

    /* checking connection */
    if (db.testConnection()) {

        try {

            sql::ResultSet *res;
            sql::PreparedStatement *pstmt; //using prepared statement

            pstmt = db.con->prepareStatement("SELECT money_balance, bank_code FROM wallets WHERE id = ?"); //sql injection
            pstmt->setInt(1, user.getId());
            res = pstmt->executeQuery();

            while (res->next()) {

                this->setMoneyBalance(res->getDouble("money_balance"));
                this->setBankCode(res->getString("bank_code"));

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

void Bank::updateBalanceInfo(float newBalance) {

    if (this->db.testConnection()) {

        try {

            sql::PreparedStatement *pstmt; //using prepared statement

            pstmt = this->db.con->prepareStatement("UPDATE wallets SET money_balance = ? WHERE user_id = ?"); //sql injection
            pstmt->setDouble(1, newBalance);
            pstmt->setInt(2, this->user.getId());
            pstmt->executeUpdate();

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

void Bank::recordTransaction(string type, User toUser, float moneyAmount){

    if (this->db.testConnection()) {

        try {

            sql::PreparedStatement *pstmt; //using prepared statement

            pstmt = this->db.con->prepareStatement("INSERT INTO wallet_transactions (type, from_wallet_id, to_wallet_id, money_amount, date_time) VALUES (?, ?, ?, ?, ?)"); //sql injection
            pstmt->setString(1, type);
            pstmt->setInt(2, this->user.getId());
            pstmt->setInt(3, toUser.getId());
            pstmt->setDouble(4, moneyAmount);

            TimeInfo time;
            pstmt->setString(5,"2021-01-11 00:00:00");
            //time.getTimePtr()->tm_year + "-" + time.getTimePtr()->tm_mon + "-" + time.getTimePtr()->tm_mday + " " + time.getTimePtr()->tm_hour + ":" + time.getTimePtr()->tm_min + ":" + time.getTimePtr()->tm_sec);
            pstmt->executeUpdate();

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

string Bank::payment(Item item, User &toUser) {

    float difference = this->getMoneyBalance() - item.getPrice();

    try {
        if (this->db.testConnection()) {
            if (difference >= 0) {
                this->updateBalanceInfo(difference);
                Bank sellerBank(toUser);
                sellerBank.updateBalanceInfo(sellerBank.getMoneyBalance() + item.getPrice());
                this->recordTransaction("Payment", toUser, item.getPrice());
                return ("SUCCESS!");
            }
            else
                throw "Insufficent balance";
        } else
            throw "Connection error";
    }
    catch (char const *error) {                                    //using char array because strings are not allowed
       return(error);
    }
}

void Bank::setMoneyBalance(float moneyBalance) {
    Bank::moneyBalance = moneyBalance;
}

const string &Bank::getBankCode() const {
    return bankCode;
}

void Bank::setBankCode(const string &bankCode) {
    Bank::bankCode = bankCode;
}

float Bank::getMoneyBalance() const {
    return moneyBalance;
}
