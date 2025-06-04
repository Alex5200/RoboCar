#pragma once
#include <Arduino.h>

class PIDController {
public:
    PIDController(float kp, float ki, float kd);
    void reset();
    float compute(float target, float current);
    bool isDone(float error) const;
    
private:
    const float kp_;
    const float ki_;
    const float kd_;
    float integral_ = 0;
    float lastError_ = 0;
    const float tolerance_ = 20.0f;
};