
/*!
 *  @brief     Simulation of two F_CITY scenarios, payment and ticket stamp.
 *  @details   https://sites.google.com/studentmail.unicas.it/fcity-project/home
 *  @author    Marco Napoleone
 *  @author    Alessandro Ricci
 *  @author    Roman Capraro
 *  @version   1.30.1+beta
 *  @date      2019-2020
 *  @pre       get mySQL lib for your system
 *  @bug       possible memory leak, more testing needed
 *  @copyright GNU Public License.
 */

#include <iostream>
#include "User.h"
#include "Transport/Ticket.h"
#include "auxiliary-lib/TimeInfo.h"
#include "Payment/Bank.h"
#include "Payment/Shop.h"
#include "Hardware/Hardware.h"

/** \note Ignoring noreturn */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

#define host "tcp://db4free.net:3306"
#define userName "fcitydb"
#define pw "KFEIUGEudu$"

using namespace hardware;

int main() {

    Feedback feedback;
    Rc522 nfcReader;

    /** \note infinite loop*/
    while (true) {

        Database *db = new Database(host, userName, pw);

        /**
         * \brief Choose which scenario to be executed:
         * 0 -> PAYMENT,
         * 1 -> VALIDATE BUS TICKET"
         */
        feedback.print("Choose: ", true);
        int choice = feedback.buttonChoice();
        //feedback.good();

        /** Simulating 2 different scenarios */
        if (choice) {

            /** ticket validation */
            feedback.print("Ticket", true);
            feedback.print("stamp: ", false, 0, 1);
            feedback.good();
            delay(1500);

            /// checking connection
            if (!db->testConnection()) {
                feedback.print("CON_ERR", true);
                feedback.bad();
                break;
            }

            TimeInfo now;
            feedback.print(now.timeDate(), true);
            feedback.print("Stamp here", false, 0, 1);

            /** system listening for tag */
            feedback.listen();
            User *traveler = new User(*db, nfcReader.readTag());
            feedback.good();

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
                feedback.print("Invalid!", true);
                feedback.bad();
                delay(1500);
            } else {
                feedback.print("Thanks!", true);
                feedback.good();
                delay(1500);
            }
            delete db, traveler;

        } else {

            /** Payment */
            feedback.print("Payment", true);
            feedback.good();
            delay(1500);

            srand(time(NULL));
            int userRandId = rand() % 4 + 1;

            /** checking connection */
            if (!db->testConnection()) {
                feedback.print("CON_ERR", true);
                feedback.bad();
                break;
            }

            User *seller = new User(*db, userRandId);
            Shop *shop = new Shop(*seller);

            int itemRand = rand() % shop->getItems().size();
            auto item = shop->getItems().at(itemRand);

            /** printing item specs */
            feedback.print(item.getName(), true);
            feedback.print(std::to_string(setPrecision(item.getPrice(), 2)) + " €", false, 0, 1);

            /** system listening for tag */
            feedback.listen();
            string UID = nfcReader.readTag();
            //feedback.good();

            feedback.print("Processing...", true);

            User *buyer = new User(*db, UID);
            Bank *buyerBank = new Bank(*buyer);
            /** make the payment */
            int result = buyerBank->payment(item, *seller);

            /**
             *@if result is successful
             * payment done.
             *@endif
             *@ifnot
             * try again.
             *@endif
             */
            if (result == PAYMENT_SUCCESSFUL) {
                feedback.print("Success!", true);
                feedback.good();
                delay(1500);
            } else {
                feedback.print("ERROR!", true);
                feedback.bad();
                delay(1500);
            }

            delete db, buyer, buyerBank, seller, shop;
        }
    }
    return 0;
}


#pragma clang diagnostic pop
