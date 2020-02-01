#include <iostream>
#include "User.h"
#include "Ticket.h"
//#include "Database.h"
#include "TimeInfo.h"
#include "Bank.h"

using namespace std;

int main() {

    /* We are about to simulate 2 different scenarios */
    bool scenario;
    cout << "Choose which scenario to be executed\n0 -> PAYMENT\n1 -> VALIDATE BUS TICKET\n";
    cin >> scenario;

    /* this is the ticket validation scenario */
    if (scenario) {

        User *user = new User();
        Ticket *tic = new Ticket(*user);
        Database *db = new Database("tcp://remotemysql.com:3306", "bvYXzisyGu", "DfBbNrL9ER");
        TimeInfo tim;


        /* fetching from db and setting user class "name" and other user data */
        user->getUserInfo(*db, 3);
        cout << user->getName() << user->getSurname() << " " << user->getBirthDate() << " " << user->getGender() << endl;

        delete user, tic, tim, db;

    }
    /* this is the ticket validation scenario */
    else{

        User *user = new User();
        Bank *bank = new Bank(*user);
        //

    //
        //get a shop and an item randomly from the list of the available shops and ask for payment
        //then when a RFiD tag is near check if the money are enough to continue.
        //subsequently move the money amount (item.price) from the buyer to the seller, that's it, easy ?


    }
    return EXIT_SUCCESS;
}

