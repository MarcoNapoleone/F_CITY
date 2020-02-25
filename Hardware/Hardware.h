//
// Created by makon on 09/02/2020.
//

#ifndef F_CITY_HARDWARE_H
#define F_CITY_HARDWARE_H

#include <wiringPi.h>
#include <lcd.h>

#define LCD_RS 25 /** @def Register select pin */
#define LCD_E 24 /** @def Enable Pin */
#define LCD_D4 23 /** @def Data pin 4 */
#define LCD_D5 22 /** @def Data pin 5 */
#define LCD_D6 21 /** @def Data pin 6 */
#define LCD_D7 29 /** @def Data pin 7 */
#define LED_R 1 /** @def red led */
#define LED_G 26 /** @def green led */
#define BUTTON_Y 27 /** @def yellow button */
#define BUTTON_R 28 /** @def red button */
#define BUZ 4 /** @def buzzer */

using namespace std;

/**
 * this create a groups of elements
 */
namespace hardware {

    /**
     * this is the digital input/output interface to communicate with a human
     */
    class DigitalIO {

    public:

        /**
         * wait until a button is pressed
         * @return the button chosen (yellow or red)
         */
        int buttonChoice();

        /**
         * set the led green high to indicate that the system is ready to read a tag
         */
        void listen();

        /**
         * make all light feedback low
         */
        void ledClear();

    protected:

        /**
         * used to initialize the pin mode of the components (I/O)
         */
        void setup();

        /**
         * used to change the state of a led from HIGH to LOW and viceversa
         * @param led which led
         * @param state 1 to HIGH and 0 to LOW
         */
        void setLed(int led, bool state);
    };

    /**
     * this is used to implement the LCD module
     */
    class Lcd {

    protected:
        int lcd;

    public:

        /**
         * this print /p text on the lcd
         * @tparam T1 can be a float, a std::string, an int or a char const* type
         * @param text
         */
        template<typename T1>
        void print(T1 text);

        /**
         * this print /p text on the lcd without clearing the screen to add text on [ROW, COL]
         * @tparam T2  can be a float, a std::string, an int or a char const* type
         * @param text
         * @param col 0 for the first slot to 15
         * @param row 0 or 1 in this configuration
         */
        template<typename T2>
        void print(T2 text, const int col, const int row);

    protected:

        /**
         *  used to initialize the LCD
         */
        void setup();
    };

    /**
     * this is the main interface to communicate with a human user
     */
    class Feedback : public DigitalIO, public Lcd {

    public:

        /**
         * used to give a positive feedback
         */
        void good();

        /**
         * used to give a negative feedback
         */
        void bad();

        /**
         * used to clear both LEDs and LCD
         */
        void clear();

        Feedback();

    };

    /**
     * this is used to implement the RC522 module
     */
    class Rc522 {

    private:

        std::string uid;

    public:

        /**
         * this will run a python script that get the NFC tag UID
         * @note you must approach the NFC tag to break the cycle, forcing the exit will cause problem to the GPIO SPI
         * @return the UID of the user
         */
        std::string readTag();
    };

};


#endif //F_CITY_HARDWARE_H
