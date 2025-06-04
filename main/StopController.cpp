#include "StopController.h"

StopController::StopController() {}

void StopController::begin() {
    pinMode(stopA, OUTPUT);
    pinMode(stopB, OUTPUT);
    digitalWrite(stopA, LOW);
    digitalWrite(stopB, LOW);
}

void StopController::processCommand(char command) {
    if (command == 's') stopRequested = true;
    else if (command == 'r') runRequested = true;
}

void StopController::update() {
    if (stopRequested && analogRead(potStop) < stopOn - 3) {
        digitalWrite(stopA, LOW);
        digitalWrite(stopB, HIGH);
    } 
    else if (runRequested && analogRead(potStop) > stopOff + 3) {
        digitalWrite(stopA, HIGH);
        digitalWrite(stopB, LOW);
    } 
    else {
        digitalWrite(stopA, LOW);
        digitalWrite(stopB, LOW);
    }
    stopRequested = false;
    runRequested = false;
}