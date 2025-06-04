#include <Arduino.h>
#include "config.h"
#include "MotorController.h"
#include "StopController.h"
#include "PIDController.h"

MotorController motor;
StopController stopController;
PIDController pid(Kp, Ki, Kd);

bool loggingEnabled = false;
int targetValue = 0;
bool newTargetAvailable = false;

void setup() {
    Serial.begin(115200);
    motor.begin(pwmPinForward, pwmPinBackward);
    stopController.begin();
    pinMode(angleSensor, INPUT);
}

void loop() {
    // Обработка входящих данных
    if (Serial.available()) {
        char c = Serial.read();
        
        if (c == ':') {
            targetValue = Serial.parseInt();
            newTargetAvailable = true;
            Serial.print("Value: ");
            Serial.println(targetValue);
        } 
        else {
            switch(c) {
                case 's': case 'r': 
                    stopController.processCommand(c);
                    break;
                case 'l': 
                    loggingEnabled = true;
                    break;
                case 'b': 
                    loggingEnabled = false;
                    break;
            }
        }
    }

    stopController.update();
    
    if (loggingEnabled) {
        Serial.print("PotStop: ");
        Serial.println(analogRead(potStop));
        Serial.print("target_angle: ");
        Serial.println(analogRead(angleSensor));
    }

    // Управление мотором через PID
    if (targetValue >= 240 && targetValue <= 840) {
        if (newTargetAvailable) {
            pid.reset();
            newTargetAvailable = false;
        }
        
        int currentAngle = analogRead(angleSensor);
        float error = targetValue - currentAngle;
        
        if (pid.isDone(error)) {
            motor.setSpeed(0);
        } else {
            float output = pid.compute(targetValue, currentAngle);
            motor.setSpeed(output / 2);
            
            Serial.print("Target: ");
            Serial.print(targetValue);
            Serial.print(" Current: ");
            Serial.print(currentAngle);
            Serial.print(" Output: ");
            Serial.println(output);
        }
    } else {
        motor.setSpeed(0);
    }
    
    delay(1);
}