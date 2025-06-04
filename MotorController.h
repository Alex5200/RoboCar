#pragma once
#include <Arduino.h>

class MotorController {
public:
    MotorController();
    void begin(int pinForward, int pinBackward);
    void setSpeed(float speed);
    
private:
    int pinForward_;
    int pinBackward_;
};