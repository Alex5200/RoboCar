#pragma once
#include <Arduino.h>

class GearboxController {
public:
    enum class GearMode {
        PARK,
        REVERSE,
        DRIVE,
        UNKNOWN
    };

    GearboxController(int potPin, int pinA, int pinB);
    void begin();
    void update();
    GearMode getCurrentGear() const;
    
    void setThresholds(int parkMax, int reverseMin, int reverseMax, int driveMin);

private:
    const int potPin_;
    const int pinA_;
    const int pinB_;
    
    int parkMax_ = 300;
    int reverseMin_ = 301;
    int reverseMax_ = 600;
    int driveMin_ = 601;
    
    GearMode currentGear_ = GearMode::PARK;
    int lastRawValue_ = 0;
    
    void setGear(GearMode gear);
};