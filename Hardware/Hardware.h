//
// Created by makon on 09/02/2020.
//

#ifndef F_CITY_HARDWARE_H
#define F_CITY_HARDWARE_H

#include <wiringPi.h>
#include <lcd.h>

using namespace std;

class Hardware {

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

public:
    Hardware();

    int buttonChoice();

    void setLed(int led, bool state);

    void errorFeedback();

    void bipFeedback();
};


#endif //F_CITY_HARDWARE_H
