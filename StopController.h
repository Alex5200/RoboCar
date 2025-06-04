#pragma once
#include <Arduino.h>
#include "config.h"

class StopController {
public:
    StopController();
    void begin();
    void processCommand(char command);
    void update();
    
private:
    bool stopRequested = false;
    bool runRequested = false;
};