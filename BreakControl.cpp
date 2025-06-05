#include "BreakControl.h"

BreakControl::BreakControl() {}

void BreakControl::begin(int pinForward, int pinBackward) {
    breakcontact1_ = breakcontact1;
    breakcontact2_ = breakcontact2;
    pinMode(breakcontact1_, OUTPUT);
    pinMode(breakcontact2_, OUTPUT);
    setSpeed(0);
}

void BreakControl::setSpeed(float speed) {
    if (speed > 0) {
        analogWrite(breakcontact1_, speed);
        analogWrite(breakcontact2_, 0);
    } else if (speed < 0) {
        analogWrite(breakcontact1_, 0);
        analogWrite(breakcontact2_, -speed);
    } else {
        analogWrite(breakcontact1_, 0);
        analogWrite(breakcontact2_, 0);
    }
}