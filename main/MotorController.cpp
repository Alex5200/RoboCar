#include "MotorController.h"

MotorController::MotorController() {}

void MotorController::begin(int pinForward, int pinBackward) {
    pinForward_ = pinForward;
    pinBackward_ = pinBackward;
    pinMode(pinForward_, OUTPUT);
    pinMode(pinBackward_, OUTPUT);
    setSpeed(0);
}

void MotorController::setSpeed(float speed) {
    if (speed > 0) {
        analogWrite(pinForward_, speed);
        analogWrite(pinBackward_, 0);
    } else if (speed < 0) {
        analogWrite(pinForward_, 0);
        analogWrite(pinBackward_, -speed);
    } else {
        analogWrite(pinForward_, 0);
        analogWrite(pinBackward_, 0);
    }
}