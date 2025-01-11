#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Ps3Controller.h>

class PS3Controller {
public:
    PS3Controller();
    void begin();
    int16_t getLeftStickX();
    int16_t getLeftStickY();
    int16_t getRightStickX();
    bool isConnected();
    static bool up, down, left, right, triangle, circle, cross, square, L1, L2, R1, R2, select, start;
private:
    static void notify();
    static void onConnect();
    static void onDisconnect();
};

#endif
