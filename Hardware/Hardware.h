//
// Created by makon on 09/02/2020.
//

#ifndef F_CITY_HARDWARE_H
#define F_CITY_HARDWARE_H

#include <wiringPi.h>
#include <lcd.h>

#define LCD_RS 25 //Register select pin
#define LCD_E 24 //Enable Pin
#define LCD_D4 23 //Data pin 4
#define LCD_D5 22 //Data pin 5
#define LCD_D6 21 //Data pin 6
#define LCD_D7 29 //Data pin 7
#define LED_R 1 //red led
#define LED_G 26 //green led
#define BUTTON_Y 27 //yellow button
#define BUTTON_R 28 //red button
#define BUZ 4 // buzzer

using namespace std;

namespace hardware {

    class DigitalIO {
    public:
        int buttonChoice();

        void listen();

    protected:
        void setup();

        void clear();

        void setLed(int led, bool state);
    };

    class Lcd {
    private:
        int lcd;

    public:
        void print(string text, bool clear);

        void print(string, bool clear, int col, int row);

    protected:
        void setup();
    };

    class Feedback : public DigitalIO, public Lcd {
    private:

    public:
        void good();

        void bad();

        Feedback();

    };

    class Rc522 {
    private:
        std::string uid;

    public:
        std::string readTag();
    };


};


#endif //F_CITY_HARDWARE_H
