// filepath: PropulsionStepper/src/PropulsionStepper.cpp
#include "PropulsionStepper.h"

PropulsionStepper::PropulsionStepper(int stepPin, int dirPin, int enablePin)
    : _stepPin(stepPin), _dirPin(dirPin), _enablePin(enablePin),
      _targetSpeed(0), _currentSpeed(0), _acceleration(0),
      _lastStepTime(0), _lastSpeedUpdateTime(0), _currentPosition(0), _targetPosition(0),
      _moveSpeed(100) {
    pinMode(_stepPin, OUTPUT);
    pinMode(_dirPin, OUTPUT);
    pinMode(_enablePin, OUTPUT);
    digitalWrite(_enablePin, LOW); // Enable motor driver
}

PropulsionStepper::PropulsionStepper(int stepPin, int dirPin)
    : _stepPin(stepPin), _dirPin(dirPin), _enablePin(-1),
      _targetSpeed(0), _currentSpeed(0), _acceleration(0),
      _lastStepTime(0), _lastSpeedUpdateTime(0), _currentPosition(0), _targetPosition(0),
      _moveSpeed(100) {
    pinMode(_stepPin, OUTPUT);
    pinMode(_dirPin, OUTPUT);
}

float PropulsionStepper::acceleration() const {
    return _acceleration;
}

bool PropulsionStepper::isMoving() const {
    if (_mode == STEP_MOVEMENT) {
        return _targetPosition != _currentPosition;
    }
    else if (_mode == CONTINUOUS_MOVEMENT) {
        return _targetSpeed != 0 || _currentSpeed != 0;
    }
    else {
        return false;
    }
}

bool PropulsionStepper::isSpinning() const {
    return isSpinning();
}

bool PropulsionStepper::isPoweredOn() const {
    if (_enablePin == -1) {
        return true;
    }
    return digitalRead(_enablePin) == LOW;
}

void PropulsionStepper::loop() {
    unsigned long currentTime = micros();

    switch (_mode) {
        case STOPPED:
            break;

        case CONTINUOUS_MOVEMENT:
            if (_targetSpeed != 0 || _currentSpeed != 0) {
                driveMotor();
            }
            break;

        case STEP_MOVEMENT:
            if (_targetPosition != _currentPosition) {
                int dir = (_targetPosition - _currentPosition) > 0 ? 1 : -1;
                long stepsRemaining = abs(_targetPosition - _currentPosition);
                float distanceToStop = (_currentSpeed * _currentSpeed) / (2 * _acceleration);
                if (stepsRemaining <= distanceToStop) {
                    _targetSpeed = 0;
                }
                else {
                    _targetSpeed = _moveSpeed * dir;
                }
                driveMotor();
            }
            break;
    }
}

void PropulsionStepper::moveAbsolute(long targetPosition, float speed) {
    _mode = STEP_MOVEMENT;
    if (!isMoving()) {
        _lastSpeedUpdateTime = micros();
        _lastStepTime = micros();
    }
    _targetPosition = targetPosition;
    _moveSpeed = speed;
    loop();
}

void PropulsionStepper::moveRelative(long steps, float speed) {
    _mode = STEP_MOVEMENT;
    if (!isMoving()) {
        _lastSpeedUpdateTime = micros();
        _lastStepTime = micros();
    }
    _targetPosition = _currentPosition + steps;
    _moveSpeed = speed;
    loop();
}

long PropulsionStepper::position() const {
    return _currentPosition;
}

void PropulsionStepper::powerOff() {
    if (_enablePin != -1) {
        _currentSpeed = 0;
        digitalWrite(_enablePin, HIGH);
    }
}

void PropulsionStepper::powerOn() {
    if (_enablePin != -1) {
        digitalWrite(_enablePin, LOW);
    }
}

float PropulsionStepper::speed() const {
    return _currentSpeed;
}

void PropulsionStepper::setAcceleration(float acceleration) {
    _acceleration = acceleration;
}

void PropulsionStepper::setPosition(long position) {
    _currentPosition = position;
}

void PropulsionStepper::spin(float speed) {
    _mode = CONTINUOUS_MOVEMENT;
    if (speed == _targetSpeed) {
        return;
    }
    if (!isMoving()) {
        _lastSpeedUpdateTime = micros();
        _lastStepTime = micros();
    }
    _targetSpeed = speed;
    loop();
}

void PropulsionStepper::stop() {
    _targetSpeed = 0;
    _currentSpeed = 0;
    _mode = STOPPED;
}

void PropulsionStepper::driveMotor() {
    unsigned long currentTime = micros();

    unsigned long int deltaTime = currentTime - _lastSpeedUpdateTime;
    float speedChange = _acceleration * ((float) deltaTime / 1e6f);
    if (abs(_targetSpeed - _currentSpeed) <= speedChange) {
        _currentSpeed = _targetSpeed;
    } else {
        _currentSpeed += speedChange * ((_targetSpeed > _currentSpeed) ? 1 : -1);
    }
    _lastSpeedUpdateTime = currentTime;

    _stepDeltaTime = 1e6 / abs(_currentSpeed);
    if (currentTime - _lastStepTime >= _stepDeltaTime) {
        step();
        digitalWrite(_dirPin, (_currentSpeed > 0) ? HIGH : LOW);
        _lastStepTime = currentTime;
    }
}

void PropulsionStepper::step() {
    digitalWrite(_stepPin, HIGH);
    delayMicroseconds(1);
    digitalWrite(_stepPin, LOW);
    _currentPosition += ((_currentSpeed > 0) ? 1 : -1);
}
