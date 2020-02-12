
#ifndef F_CITY_BANK_H
#define F_CITY_BANK_H

#include "../User.h"
#include "../auxiliary-lib/Database.h"
#include "Item.h"
#include "../auxiliary-lib/TimeInfo.h"

class Bank {

private:
    User user;
    Database db;
    float moneyBalance;
    string bankCode;
public:
    float getMoneyBalance() const;

private:

    void fetchBalanceInfo();
    void updateBalanceInfo(float newBalance);
    void recordTransaction(string type, User toUser, float moneyAmmount);

public:

    Bank(User &user);
    string payment(Item item, User &toUser);
    void setMoneyBalance(float moneyBalance);
    const string &getBankCode() const;
    void setBankCode(const string &bankCode);
};


#endif //F_CITY_BANK_H
