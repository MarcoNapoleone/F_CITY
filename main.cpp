#include <iostream>
#include <cstdlib>

#include "User.h"
#include "Transport/Ticket.h"
#include "auxiliary-lib/TimeInfo.h"
#include "Payment/Bank.h"
#include "Payment/Shop.h"

#include "Hardware/Lcd.h"
#include "Hardware/Rc522.h"
#include "Hardware/Hardware.h"

#define host "tcp://remotemysql.com:3306"
#define userName "bvYXzisyGu"
#define pw "DfBbNrL9ER"


int main() {

    Hardware interface;
    Lcd lcd;
    Rc522 nfcReader;

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
            delay (1500);
            interface.setLed(LED_R, 0);
            interface.bipFeedback();

            TimeInfo now;

            lcd.print(now.timeDate(), true);
            lcd.print("Stamp ->", false, 0, 1);

            Database *db = new Database(host, userName, pw);

            if(!db->testConnection()) {
                lcd.print("CON_ERR", true);
                break;
            }

            interface.setLed(LED_G, 1);
            interface.setLed(LED_R, 0);
            User *traveler = new User(*db, nfcReader.readTag());
            interface.bipFeedback();

            Ticket ticket(*traveler);
            cout<<mktime(now.getTimePtr())<<" "<<ticket.getTicketExpDate();

            cout<<strToTime("2021-01-11 00:00:00");
            cout.flush();

            if (now >= ticket) {
                lcd.print("Invalid!", true);
                interface.errorFeedback();
            } else {
                lcd.print("Thanks!", true);
                interface.setLed(LED_G, 0);
                delay (500);
                interface.setLed(LED_G, 1);
                interface.bipFeedback();
                delay (5000);
            }
            delete traveler, db;

        } else {

            /*! Payment*/
            interface.setLed(LED_R, 1);
            lcd.print("Payment", true);
            delay (1500);
            interface.setLed(LED_R, 0);
            interface.bipFeedback();

            srand(time(NULL));
            int userRandId = rand() % 4 + 1;

            Database *db = new Database(host, userName, pw);

            if(!db->testConnection()) {
                lcd.print("CON_ERR", true);
                break;
            }

            User *seller = new User(*db, userRandId);
            Shop *shop = new Shop(*seller);

            int itemRand = rand() % shop->getItems().size() + 1;
            cout<<"1";
            cout.flush();

            auto item = shop->getItems().at(itemRand);

            lcd.print(item.getName(), true);
            lcd.print(std::to_string(item.getPrice()), false, 0, 1);

            interface.setLed(LED_G, 1);
            string UID = nfcReader.readTag();
            cout<<UID;

            User *buyer = new User(*db, UID);
            Bank *buyerBank = new Bank(*buyer);

            string result = buyerBank->payment(item, *seller);

            if (result == "SUCCESS!") {
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


