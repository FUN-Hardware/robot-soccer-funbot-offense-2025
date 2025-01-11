#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
private:
    uint8_t pin1, pin2;     // Control pins for the motor
    uint8_t channel1, channel2; // PWM channels

public:
    Motor(uint8_t pin1, uint8_t pin2, uint8_t channel1, uint8_t channel2);
    void setSpeed(int speed); // Speed range: -255 to 255
    void brake(); // Brake
};

#endif
