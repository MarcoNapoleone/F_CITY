//
// Created by makon on 09/02/2020.
//

#include <unistd.h>
#include "Hardware.h"


Hardware::Hardware() {

    wiringPiSetup();

    pinMode(LED_G, OUTPUT);
    pinMode(LED_R, OUTPUT);
    pinMode(BUTTON_Y, INPUT);
    pinMode(BUTTON_R, INPUT);
    pinMode(BUZ, OUTPUT);
}


int Hardware::buttonChoice() {

    int choice = -1;

    while (true) {

        if (digitalRead(BUTTON_R))
            return (choice = 0);
        if (digitalRead(BUTTON_Y))
            return (choice = 1);
    }
}

void Hardware::setLed(int led, bool state) {
    if (state)
        digitalWrite(led, HIGH);
    else
        digitalWrite(led, LOW);
    return;
}

void Hardware::errorFeedback() {

    digitalWrite(LED_G, LOW);

    digitalWrite(LED_R, HIGH);
    digitalWrite(BUZ, HIGH);
    delay(200);
    digitalWrite(LED_R, LOW);
    digitalWrite(BUZ, LOW);
    delay(200);

    digitalWrite(LED_R, HIGH);
    digitalWrite(BUZ, HIGH);
    delay(200);
    digitalWrite(LED_R, LOW);
    digitalWrite(BUZ, LOW);
    delay(200);

    digitalWrite(LED_R, HIGH);
    digitalWrite(BUZ, HIGH);
    delay(200);
    digitalWrite(LED_R, LOW);
    digitalWrite(BUZ, LOW);
    delay(200);
}

void Hardware::bipFeedback() {

    digitalWrite(BUZ, HIGH);
    delay(200);
    digitalWrite(BUZ, LOW);
    delay(200);
}
