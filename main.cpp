
/*!
 *  \brief     Simulation of two F_CITY scenarios, payment and ticket stamp.
 *  \details   https://sites.google.com/studentmail.unicas.it/fcity-project/home
 *  \author    Marco Napoleone
 *  \author    Alessandro Ricci
 *  \author    Roman Capraro
 *  \version   1.3
 *  \date      2019-2020
 *  \pre       get mySQL lib for your system
 *  \bug       unknown.
 *  \copyright GNU Public License.
 */

#include <iostream>
#include "User.h"
#include "Transport/Ticket.h"
#include "auxiliary-lib/TimeInfo.h"
#include "Payment/Bank.h"
#include "Payment/Shop.h"

#include "Hardware/Lcd.h"
#include "Hardware/Rc522.h"
#include "Hardware/Hardware.h"

/** \note Ignoring noreturn */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

#define host "jdbc:mysql://db4free.net:3306/fcitydb"
#define userName "fcitydb"
#define pw "KFEIUGEudu$"

int main() {

    Hardware interface;
    Lcd lcd;
    Rc522 nfcReader;

    lcd.scrollMessage(0, 36, "F_CITY project v1.4a test scrolling");

    /** \note infinite loop*/
    while (true) {

        Database *db = new Database(host, userName, pw);

        /**
         * \brief Choose which scenario to be executed:
         * 0 -> PAYMENT,
         * 1 -> VALIDATE BUS TICKET"
         */
        lcd.print("Choose: ", true);
        int choice = interface.buttonChoice();

        /** Simulating 2 different scenarios */
        if (choice) {

            /** ticket validation */
            interface.setLed(LED_R, 1);
            lcd.print("Ticket", true);
            lcd.print("stamp: ", false, 0, 1);
            delay(1500);
            interface.setLed(LED_R, 0);
            interface.bipFeedback();

            /// checking connection
            if (!db->testConnection()) {
                lcd.print("CON_ERR", true);
                break;
            }

            TimeInfo now;
            lcd.print(now.timeDate(), true);
            lcd.print("Stamp ->", false, 0, 1);
            interface.setLed(LED_G, 1);
            interface.setLed(LED_R, 0);

            /** system listening for tag */
            User *traveler = new User(*db, nfcReader.readTag());
            interface.bipFeedback();

            Ticket ticket(*traveler);

            /**
             *\if actual time is bigger than the ticket expiring date
             *  ticket rejected.
             *\endif
             *\ifnot
             *  ticket is valid.
             *\endif
             */
            if (now >= ticket) {
                lcd.print("Invalid!", true);
                interface.errorFeedback();
            } else {
                lcd.print("Thanks!", true);
                interface.setLed(LED_G, 0);
                delay(500);
                interface.setLed(LED_G, 1);
                interface.bipFeedback();
                delay(2000);
            }
            delete db, traveler;

        } else {

            /** Payment */
            interface.setLed(LED_R, 1);
            lcd.print("Payment", true);
            delay(1500);
            interface.setLed(LED_R, 0);
            interface.bipFeedback();

            srand(time(NULL));
            int userRandId = rand() % 4 + 1;

            /** checking connection */
            if (!db->testConnection()) {
                lcd.print("CON_ERR", true);
                break;
            }

            User *seller = new User(*db, userRandId);
            Shop *shop = new Shop(*seller);

            int itemRand = rand() % shop->getItems().size();
            auto item = shop->getItems().at(itemRand);

            /** printing item specs */
            lcd.print(item.getName(), true);
            lcd.print(std::to_string(item.getPrice()), false, 0, 1);

            /** system listening for tag */
            interface.setLed(LED_G, 1);
            string UID = nfcReader.readTag();

            User *buyer = new User(*db, UID);
            Bank *buyerBank = new Bank(*buyer);

            /** make the payment */
            string result = buyerBank->payment(item, *seller);

            /**
             *\if result is successful
             * payment done.
             *\endif
             *\ifnot
             * try again.
             *\endif
             */
            if (result == "SUCCESS!") {
                lcd.print(result, true);
                interface.bipFeedback();
            } else {
                lcd.print("ERROR!", true);
                lcd.print("TRY AGAIN", false, 0, 1);
                interface.errorFeedback();
            }

            delete db, buyer, buyerBank, seller, shop;
        }
    }
    return 0;
}


#pragma clang diagnostic pop
