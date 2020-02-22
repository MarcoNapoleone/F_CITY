
#ifndef F_CITY_BANK_H
#define F_CITY_BANK_H

#include "../User.h"
#include "../auxiliary-lib/Database.h"
#include "Item.h"
#include "../auxiliary-lib/TimeInfo.h"

#define PAYMENT_SUCCESSFUL 1
#define INSUF_BALANCE 0
#define CON_ERR -1

class Bank {

private:
    User user;
    Database db;
    float moneyBalance;
    string bankCode;

    void fetchBalanceInfo();

    void updateBalanceInfo(float newBalance);

    void recordTransaction(string type, User toUser, float moneyAmount);

public:

    Bank(User &user);

    int payment(Item item, User &toUser);

    void setMoneyBalance(float moneyBalance);

    float getMoneyBalance() const;

    const string &getBankCode() const;

    void setBankCode(const string &bankCode);
};


#endif //F_CITY_BANK_H
