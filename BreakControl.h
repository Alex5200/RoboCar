#include <Arduino.h>

class BreakControl {
public:
    MotorController();
    void begin(int breakcontact1, int breakcontact2);
    void setSpeed(float speed);
    
private:
    int breakcontact1_;
    int breakcontact2_;
};