#include <iostream>
#include "User.h"
#include "Transport/Ticket.h"
#include "auxiliary-lib/TimeInfo.h"
#include "Payment/Bank.h"
#include "Payment/Shop.h"
#include <stdlib.h>
#include "Hardware/Lcd.h"
#include "Hardware/Rc522.h"
#include "Hardware/Hardware.h"

#define host "tcp://remotemysql.com:3306"
#define userName "bvYXzisyGu"
#define pw "DfBbNrL9ER"


int main() {

    Hardware interface;
    Lcd lcd;
    Rc522 rfid;

    while (true) {

        /*! Choose which scenario to be executed: 0 -> PAYMENT, 1 -> VALIDATE BUS TICKET" */
        lcd.print("Choose: ", true);
        int choice = interface.buttonChoice();

        /* Simulating 2 different scenarios */
        if (choice) {

            /*! ticket validation */
            interface.setLed(LED_R, 1);
            lcd.print("Ticket", true);
            lcd.print("stamp: ", false, 0, 1);
            sleep(1);

            TimeInfo tim;

            lcd.print(tim.timeDate(), true);
            lcd.print("Stamp", false, 0, 1);

            Database *db = new Database(host, userName, pw);
            if(db->testConnection()) {
                lcd.print("CON_ERR", true);
                break;
            }

            interface.setLed(LED_G, 1);
            interface.setLed(LED_R, 0);
            User *user = new User(*db, rfid.readTag());
            interface.bipFeedback();

            Ticket tic(*user);

            if (tim >= tic) {
                lcd.print("Invalid!", true);
                interface.errorFeedback();
            } else {
                lcd.print("Thanks!", true);
                interface.setLed(LED_G, 0);
                sleep(0.5);
                interface.setLed(LED_G, 1);
                interface.bipFeedback();
                sleep(5);
            }
            delete user, tic, tim, db;

        } else {

            /*! Payment*/
            interface.setLed(LED_R, 1);
            lcd.print("Payment", true);
            sleep(1);

            string UID = rfid.readTag();

            srand(time(nullptr));
            int userRandId = rand() % 4 + 1;

            Database *db = new Database(host, userName, pw);
            if(db->testConnection()) {
                lcd.print("CON_ERR", true);
                break;
            }

            User *buyer = new User(*db, UID);
            User *seller = new User(*db, userRandId);

            Bank *buyerBank = new Bank(*buyer);
            Shop *shop = new Shop(*seller);

            int itemRand = rand() % shop->getItems().size() + 1;

            string result = buyerBank->payment(shop->getItems().at(itemRand), *seller);

            if (result == "SUCCES!") {
                lcd.print(result, true);
                interface.bipFeedback();
            } else {
                lcd.print("ERROR!", true);
                lcd.print("TRY AGAIN", false, 0, 1);
                interface.errorFeedback();
            }
            delete buyer, buyerBank, seller, shop, db;

        }
    }
}


