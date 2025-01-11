#include "Motor.h"

Motor::Motor(uint8_t pin1, uint8_t pin2, uint8_t channel1, uint8_t channel2)
    : pin1(pin1), pin2(pin2), channel1(channel1), channel2(channel2) {
    // Initialize pins
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);

    // Attach pins to PWM channels
    ledcAttachPin(pin1, channel1);
    ledcAttachPin(pin2, channel2);

    // Configure PWM channels
    ledcSetup(channel1, 5000, 8); // 5kHz, 8-bit resolution
    ledcSetup(channel2, 5000, 8); // 5kHz, 8-bit resolution
}

void Motor::setSpeed(int speed) {
    speed = constrain(speed, -255, 255);

    if (speed > 0) {
        // Forward
        ledcWrite(channel1, speed);
        ledcWrite(channel2, 0);
    } else if (speed < 0) {
        // Reverse
        ledcWrite(channel1, 0);
        ledcWrite(channel2, -speed);
    } else {
        // Stop
        ledcWrite(channel1, 0);
        ledcWrite(channel2, 0);
    }
}

void Motor::brake() {
    ledcWrite(pin1, 255);
    ledcWrite(pin2, 255);
}