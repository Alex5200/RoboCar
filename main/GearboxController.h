class GearboxController {
public:
    enum class GearMode {
        PARK,
        REVERSE,
        DRIVE,
        UNKNOWN
    };

    GearboxController(int potPin, int pinA, int pinB);
    void begin();
    void update();
    GearMode getCurrentGear() const;
    
    void setThresholds(int parkMax, int reverseMin, int reverseMax, int driveMin);
    void setGear(GearMode gear); // Перемещено в public

private:
    const int potPin_;
    const int pinA_;
    const int pinB_;
    
    int parkMax_ = 300;
    int reverseMin_ = 301;
    int reverseMax_ = 600;
    int driveMin_ = 601;
    
    GearMode currentGear_ = GearMode::PARK;
    int lastRawValue_ = 0;
};