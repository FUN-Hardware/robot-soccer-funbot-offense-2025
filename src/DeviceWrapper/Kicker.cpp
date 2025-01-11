#include "Kicker.h"

Kicker::Kicker() {
    motor = new Motor(0, 5, 8, 9);
    pinMode(34, INPUT);
}

void Kicker::kick() {
    motor->setSpeed(255);
}

void Kicker::hold() {
    motor->setSpeed(-255);
}

void Kicker::stop() {
    motor->setSpeed(0);
    Serial.print("reflect;");
    Serial.println(analogRead(34));
}
