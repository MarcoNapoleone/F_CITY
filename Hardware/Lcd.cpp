//
// Created by makon on 10/02/2020.
//

#include "Lcd.h"

void Lcd::setup() {

    wiringPiSetup();
    lcd = lcdInit(2, 8, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);
    return;
}

void Lcd::print(string text, bool clear) {

    if (clear) lcdClear(lcd);

    lcdPosition(lcd, 0, 0);
    lcdPuts(lcd, text);
    return;
}

void Lcd::print(string text, bool clear, int col, int row) {

    if (clear) lcdClear(lcd);
    lcdPosition(lcd, col, row);
    lcdPuts(lcd, text);
    return;
}

Lcd::Lcd() {
    this->setup();
}
