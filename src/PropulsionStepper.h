// filepath: PropulsionStepper/src/PropulsionStepper.h
#ifndef PROPULSIONSTEPPER_H
#define PROPULSIONSTEPPER_H

#include <Arduino.h>

class PropulsionStepper {
public:
    PropulsionStepper(int stepPin, int dirPin, int enablePin);
    PropulsionStepper(int stepPin, int dirPin, int enablePin, bool invertEnable);
    PropulsionStepper(int stepPin, int dirPin);
    
    float acceleration() const;
    void enableAutoOff(bool enable);
    void invertDirection(bool invert);
    void invertEnable(bool invert);
    bool isMoving() const;
    bool isSpinning() const;
    bool isPoweredOn() const;
    void loop();
    void moveAbsolute(long targetPosition, float speed);
    void moveRelative(long steps, float speed);
    long position() const;
    void powerOff();
    void powerOn();
    float speed() const;
    void setAcceleration(float acceleration);
    void setPosition(long position);
    void spin(float speed);
    void stop();

private:
    void driveMotor();
    void step();

    int _stepPin;
    int _dirPin;
    int _enablePin;
    bool _invertDirection;
    bool _invertEnable;
    bool _autoOffEnabled;
    float _targetSpeed;
    float _currentSpeed;
    float _acceleration;
    unsigned long _lastStepTime;
    unsigned long _lastSpeedUpdateTime;
    long _currentPosition;
    long _targetPosition;
    float _moveSpeed;
    enum Mode { STOPPED, CONTINUOUS_MOVEMENT, STEP_MOVEMENT } _mode;
    unsigned long _stepDeltaTime;
};

#endif // PROPULSIONSTEPPER_H
