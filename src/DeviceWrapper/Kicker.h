#ifndef KICKER_H
#define KICKER_H

#include "Motor.h"
#include <Arduino.h>

class Kicker {
private:
    Motor *motor;

public:
    Kicker();
    void kick();
    void hold();
    void stop();
};

#endif
