#ifndef F_CITY_BANK_H
#define F_CITY_BANK_H

#include "../User.h"
#include "../auxiliary-lib/Database.h"
#include "Item.h"
#include "../auxiliary-lib/TimeInfo.h"

#define PAYMENT_SUCCESSFUL 1
#define INSUF_BALANCE 0
#define CON_ERR -1

/**
 * this is the bank account of the user
 */
class Bank {

private:
    User user;
    Database db;
    float moneyBalance;
    string bankCode;

    /**
     * This fetch all the bank information of the user
     */
    void fetchBalanceInfo();

    /**
     * this is is used to update the balance value of the bank account
     * @param newBalance the new balance of the user
     */
    void updateBalanceInfo(float newBalance);

    /**
     * this is used to keep tracking of transactions
     * @param type the type of the transactions (payment, withdraw, ect)
     * @param toUser the trade beneficiary
     * @param moneyAmount the money that are moved
     */
    void recordTransaction(string type, User toUser, float moneyAmount);

public:

    /**
     * constructor
     * @param user to identify the bank account
     */
    Bank(User &user);

    /**
     * this is the payment method referred to a trade of an item
     * @param item the object that is bought
     * @param toUser the trede beneficiary
     * @return a) -1 means connection error b) 0 means insufficient balance c) 1 means payment done successful
     */
    int payment(Item item, User &toUser);

    void setMoneyBalance(float moneyBalance);

    float getMoneyBalance() const;

    void setBankCode(const string &bankCode);
};


#endif //F_CITY_BANK_H
