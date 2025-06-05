#pragma once

// ===========================================
// Конфигурация пинов
// ===========================================

// Управление двигателем руля
constexpr int pwmPinForward = 5;
constexpr int pwmPinBackward = 9;

// ========================
// Конфигурация КПП
// ========================
constexpr int GEARBOX_POT_PIN = A1;  // Потенциометр коробки передач
constexpr int GEARBOX_PIN_A = 7;     // Управление режимом A
constexpr int GEARBOX_PIN_B = 2;     // Управление режимом B

// Пороговые значения для режимов КПП
constexpr int GEAR_PARK_MAX = 300;    // Максимум для режима PARK
constexpr int GEAR_REVERSE_MIN = 301; // Минимум для REVERSE
constexpr int GEAR_REVERSE_MAX = 600; // Максимум для REVERSE
constexpr int GEAR_DRIVE_MIN = 601;   // Минимум для DRIVE

// Управление акпп (стоп-сигнал)
constexpr int stopA = 7;
constexpr int stopB = 2;

// Аналоговые входы
constexpr int potStop = A1;      // Потенциометр коробки передач
constexpr int angleSensor = A0;  // Потенциометр руля для получения текущего угла

// ===========================================
// Настройки стоп-сигнала
// ===========================================
constexpr int stopOn = 180;  // Порог активации стоп-сигнала
constexpr int stopOff = 135; // Порог деактивации стоп-сигнала

// ===========================================
// Параметры PID-регулятора
// ===========================================
constexpr float Kp = 1.0;  // Пропорциональный коэффициент
constexpr float Ki = 0.1;  // Интегральный коэффициент
constexpr float Kd = 0.05; // Дифференциальный коэффициент

// ===========================================
// Дополнительные параметры
// ===========================================
constexpr float pidTolerance = 20.0f;  // Допустимая ошибка для PID
constexpr int pidOutputLimit = 255;    // Максимальное выходное значение PID
constexpr float pidTimeStep = 0.001f;  // Шаг времени для PID в секундах

// ===========================================
// Резервные пины (не используются в текущей версии)
// ===========================================
// #define btnStop 
// #define btnStart
// #define btnPause 
// #define switchLight 
// #define switchBeep