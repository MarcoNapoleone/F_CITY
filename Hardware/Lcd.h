//
// Created by makon on 10/02/2020.
//

#ifndef F_CITY_LCD_H
#define F_CITY_LCD_H

#include "Hardware.h"
#include <string>


using namespace std;

class Lcd : public Hardware {
private:
    int lcd;

public:
    void setup();

    void print(string text, bool clear);

    void print(string, bool clear, int col, int row);

    void scrollMessage (int line, int width, char *message);

    Lcd();
};


#endif //F_CITY_LCD_H
