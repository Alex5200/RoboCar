#include <Arduino.h>
#include "config.h"
#include "MotorController.h"
#include "StopController.h"
#include "PIDController.h"
#include "GearboxController.h"

// Инициализация объектов
MotorController motor;
StopController stopController;
PIDController pid(Kp, Ki, Kd);
GearboxController gearbox(GEARBOX_POT_PIN, GEARBOX_PIN_A, GEARBOX_PIN_B);

// Переменные для управления
bool loggingEnabled = false;
int targetValue = 0;
bool newTargetAvailable = false;
bool manualGearMode = false; // Флаг для ручного управления коробкой

void setup() {
    Serial.begin(115200);
    
    // Инициализация компонентов
    gearbox.begin();
    gearbox.setThresholds(
        GEAR_PARK_MAX,
        GEAR_REVERSE_MIN,
        GEAR_REVERSE_MAX,
        GEAR_DRIVE_MIN
    );
    
    motor.begin(pwmPinForward, pwmPinBackward);
    // breakcar.begin(GEARBOX_PIN_A, GEARBOX_PIN_B);
    stopController.begin();
    pinMode(angleSensor, INPUT);
    
    Serial.println("Система инициализирована. Доступные команды:");
    Serial.println("  's'/'r' - Управление стоп-контроллером");
    Serial.println("  'l'/'b' - Включить/выключить логирование");
    Serial.println("  ':' - Установить целевое значение (240-840)");
    Serial.println("  'P'/'R'/'D' - Ручное управление коробкой передач");
    Serial.println("  'A' - Автоматическое управление коробкой передач");
}

void loop() {
    // Обработка входящих команд
    if (Serial.available()) {
        char c = Serial.read();
        
        // Обработка команды установки целевого значения
        if (c == ':') {
            targetValue = Serial.parseInt();
            newTargetAvailable = true;
            Serial.print("Целевое значение установлено: ");
            Serial.println(targetValue);
        } 
        else {
            // Обработка других команд
            switch(c) {
                // Команды для стоп-контроллера
                case 's': case 'r':
                    stopController.processCommand(c);
                    break;
                
                // Команды для логирования
                case 'l': 
                    loggingEnabled = true;
                    Serial.println("Логирование включено");
                    break;
                case 'b': 
                    loggingEnabled = false;
                    Serial.println("Логирование выключено");
                    break;
                
                // Команды для ручного управления коробкой передач
                case 'P': 
                    manualGearMode = true;
                    gearbox.setGear(GearboxController::GearMode::PARK);
                    Serial.println("Режим: PARK (ручное управление)");
                    break;
                case 'R': 
                    manualGearMode = true;
                    gearbox.setGear(GearboxController::GearMode::REVERSE);
                    Serial.println("Режим: REVERSE (ручное управление)");
                    break;
                case 'D': 
                    manualGearMode = true;
                    gearbox.setGear(GearboxController::GearMode::DRIVE);
                    Serial.println("Режим: DRIVE (ручное управление)");
                    break;
                
                // Команда для автоматического управления коробкой
                case 'A': 
                    manualGearMode = false;
                    Serial.println("Автоматическое управление коробкой включено");
                    break;
                
                // Неизвестная команда
                default:
                    Serial.print("Неизвестная команда: ");
                    Serial.println(c);
            }
        }
    }

    // Обновление стоп-контроллера
    stopController.update();
    
    // Логирование данных
    if (loggingEnabled) {
        Serial.print("Потенциометр стопа: ");
        Serial.println(analogRead(potStop));
        Serial.print("Текущий угол: ");
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
            
            Serial.print("Цель: ");
            Serial.print(targetValue);
            Serial.print(" Текущее: ");
            Serial.print(currentAngle);
            Serial.print(" Выход: ");
            Serial.println(output);
        }
    } else {
        motor.setSpeed(0);
    }
    
    // Обновление состояния КПП (только в автоматическом режиме)
    if (!manualGearMode) {
        gearbox.update();
    }
    
    // Вывод текущего режима
    switch (gearbox.getCurrentGear()) {
        case GearboxController::GearMode::PARK:
            Serial.println("Режим: PARK");
            break;
        case GearboxController::GearMode::REVERSE:
            Serial.println("Режим: REVERSE");
            break;
        case GearboxController::GearMode::DRIVE:
            Serial.println("Режим: DRIVE");
            break;
        default:
            Serial.println("Режим: UNKNOWN");
    }
    
    // Дополнительная логика
    delay(100);
}