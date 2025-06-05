#include "GearboxController.h"

GearboxController::GearboxController(int potPin, int pinA, int pinB)
    : potPin_(potPin), pinA_(pinA), pinB_(pinB) {}

void GearboxController::begin() {
    pinMode(pinA_, OUTPUT);
    pinMode(pinB_, OUTPUT);
    setGear(GearMode::PARK); // Начальное состояние
}

void GearboxController::setThresholds(int parkMax, int reverseMin, int reverseMax, int driveMin) {
    parkMax_ = parkMax;
    reverseMin_ = reverseMin;
    reverseMax_ = reverseMax;
    driveMin_ = driveMin;
}

GearboxController::GearMode GearboxController::getCurrentGear() const {
    return currentGear_;
}

void GearboxController::update() {
    int rawValue = analogRead(potPin_);
    lastRawValue_ = rawValue;
    
    // Определение текущего режима по пороговым значениям
    GearMode newGear = GearMode::UNKNOWN;
    
    if (rawValue <= parkMax_) {
        newGear = GearMode::PARK;
    } 
    else if (rawValue >= reverseMin_ && rawValue <= reverseMax_) {
        newGear = GearMode::REVERSE;
    } 
    else if (rawValue >= driveMin_) {
        newGear = GearMode::DRIVE;
    }
    
    // Если режим изменился - обновляем
    if (newGear != GearMode::UNKNOWN && newGear != currentGear_) {
        setGear(newGear);
    }
}

void GearboxController::setGear(GearMode gear) {
    currentGear_ = gear;
    
    switch (gear) {
        case GearMode::PARK:
            digitalWrite(pinA_, LOW);
            digitalWrite(pinB_, LOW);
            break;
            
        case GearMode::REVERSE:
            digitalWrite(pinA_, LOW);
            digitalWrite(pinB_, HIGH);
            break;
            
        case GearMode::DRIVE:
            digitalWrite(pinA_, HIGH);
            digitalWrite(pinB_, LOW);
            break;
            
        case GearMode::UNKNOWN:
            // Безопасный режим - выключаем все
            digitalWrite(pinA_, LOW);
            digitalWrite(pinB_, LOW);
            break;
    }
}