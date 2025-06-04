#include "PIDController.h"

PIDController::PIDController(float kp, float ki, float kd) 
    : kp_(kp), ki_(ki), kd_(kd) {}

void PIDController::reset() {
    integral_ = 0;
    lastError_ = 0;
}

float PIDController::compute(float target, float current) {
    float error = target - current;
    
    integral_ += error * 0.001;
    float derivative = (error - lastError_) / 0.001;
    lastError_ = error;

    float output = kp_ * error + ki_ * integral_ + kd_ * derivative;
    
    if (output > 255) return 255;
    if (output < -255) return -255;
    return output;
}

bool PIDController::isDone(float error) const {
    return abs(error) <= tolerance_;
}