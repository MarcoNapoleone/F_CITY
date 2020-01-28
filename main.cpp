#include <iostream>
#include "User.h"
#include "Ticket.h"
//#include "Database.h"
#include "TimeInfo.h"

using namespace std;

int main() {

    /* We are about to simulate 2 different scenarios */
    bool scenario;
    cout << "Choose which scenario to be executed\n0 -> PAYMENT\n1 -> VALIDATE BUS TICKET\n";
    cin >> scenario;

    if (scenario) {

        User *user = new User();
        Ticket *tic = new Ticket(*user);
        Database *db = new Database("tcp://remotemysql.com:3306", "bvYXzisyGu", "DfBbNrL9ER");
        TimeInfo tim;


        /* fetching from db and setting user class "name" and other user data */
        user->getUserInfo(*db, 3);
        cout << user->getName() << user->getSurname() << " " << user->getBirthDate() << " " << user->getGender() << endl;



    }
    return EXIT_SUCCESS;
}

