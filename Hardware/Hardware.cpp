//
// Created by makon on 09/02/2020.
//

#include <unistd.h>
#include <fstream>
#include <cstring>
#include "Hardware.h"

using namespace hardware;

hardware::Feedback::Feedback() {
    Lcd::setup();
    DigitalIO::setup();
}

void hardware::DigitalIO::setup() {

    wiringPiSetup();

    pinMode(LED_G, OUTPUT);
    pinMode(LED_R, OUTPUT);
    pinMode(BUTTON_Y, INPUT);
    pinMode(BUTTON_R, INPUT);
    pinMode(BUZ, OUTPUT);
}

int hardware::DigitalIO::buttonChoice() {

    int choice = -1;

    while (true) {

        if (digitalRead(BUTTON_R))
            return (choice = 0);
        if (digitalRead(BUTTON_Y))
            return (choice = 1);
    }
}

void hardware::DigitalIO::setLed(int led, bool state) {

    if (state)
        digitalWrite(led, HIGH);
    else
        digitalWrite(led, LOW);
    return;
}

void hardware::DigitalIO::listen() {

    this->clear();
    setLed(LED_G, 1);
    return;
}

void hardware::DigitalIO::clear() {

    setLed(LED_G, 0);
    setLed(LED_R, 0);
    return;
}

void hardware::Lcd::setup() {

    wiringPiSetup();
    lcd = lcdInit(2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0,
                  0); /** 2 rows, 16 col, 4 bit config */
    return;
}

void hardware::Lcd::print(string text, bool clear) {

    if (clear) lcdClear(lcd);

    lcdPosition(lcd, 0, 0);
    lcdPuts(lcd, text.c_str());
    return;
}

void hardware::Lcd::print(string text, bool clear, int col, int row) {

    if (clear) lcdClear(lcd);
    lcdPosition(lcd, col, row);
    lcdPuts(lcd, text.c_str());
    return;
}

void hardware::Feedback::bad() {

    digitalWrite(LED_G, LOW);

    for (int i = 0; i < 3; i++) {

        digitalWrite(LED_R, HIGH);
        digitalWrite(BUZ, HIGH);
        delay(200);
        digitalWrite(LED_R, LOW);
        digitalWrite(BUZ, LOW);
        delay(200);
    }
    return;
}

void hardware::Feedback::good() {

    digitalWrite(LED_R, LOW);

    for (int i = 0; i < 2; i++) {

        digitalWrite(LED_G, HIGH);
        digitalWrite(BUZ, HIGH);
        delay(100);
        digitalWrite(LED_G, LOW);
        digitalWrite(BUZ, LOW);
        delay(100);
    }
    return;
}

string hardware::Rc522::readTag() {

    string UID;
    const char command[] = "python /home/pi/Desktop/F_CITY/Hardware/Read.py";
    std::system(command);
    ifstream file;
    file.open("./output.txt");
    //char output[16];
    if (file.is_open()) {
        while (!file.eof()) {
            file >> UID;
        }
    }
    file.close();
    return (UID);
}
