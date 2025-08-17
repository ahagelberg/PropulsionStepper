# PropulsionStepper Library

The `PropulsionStepper` library provides an easy-to-use interface for controlling stepper motors with Arduino. It allows for precise movement to absolute or relative positions, speed and acceleration management, as well as continuous rotation with automatic power management.

Currently the library supports only 2 or 3-pin drivers, i.e. drivers with step and direction signal with an optional enable signal (supports both active LOW and active HIGH enable pins).

## Features

- Move to absolute or relative positions with acceleration
- Continuous movement with smooth acceleration/deceleration
- Automatic power management (auto power off when idle)
- Direction inversion support
- Enable pin inversion support (active LOW/HIGH)
- Speed and acceleration control
- Manual power control (on/off)

## Installation

1. Download the `PropulsionStepper` library from the repository.
2. Extract the contents to your Arduino libraries folder, typically located at `Documents/Arduino/libraries/`.
3. Restart the Arduino IDE to recognize the new library.

## Usage

To use the `PropulsionStepper` library in your Arduino sketch, include the header file:

```cpp
#include <PropulsionStepper.h>
```

### Example

Here is a basic example of how to use the `PropulsionStepper` library:

```cpp
#include <PropulsionStepper.h>

const int stepPin = 3;
const int dirPin = 4;
const int enablePin = 5;

PropulsionStepper stepper(stepPin, dirPin, enablePin);

void setup() {
    stepper.setAcceleration(100.0);
    stepper.enableAutoOff(true); // Enable automatic power management
    stepper.moveAbsolute(200, 50.0); // Move to position 200 at speed 50
}

void loop() {
    stepper.loop(); // Call loop to update motor state
}
```

## API Reference

### Constructors

- `PropulsionStepper(int stepPin, int dirPin)` - 2-pin stepper (step, direction)
- `PropulsionStepper(int stepPin, int dirPin, int enablePin)` - 3-pin stepper (active LOW enable)
- `PropulsionStepper(int stepPin, int dirPin, int enablePin, bool invertEnable)` - 3-pin stepper with enable inversion option

### Movement Methods

- `void moveAbsolute(long targetPosition, float speed)` - Move to absolute position
- `void moveRelative(long steps, float speed)` - Move relative to current position
- `void spin(float speed)` - Continuous rotation at set speed (steps/s)
- `void stop()` - Stop motion immediately (no deceleration). To stop with deceleration use spin(0)
- `void loop()` - **Must be called regularly** to update motor state

### Configuration Methods

- `void setAcceleration(float acceleration)` - Sets the acceleration in steps/s²
- `void setPosition(long position)` - Set current position (for homing/calibration)
- `void enableAutoOff(bool enable)` - Enable automatic power off when idle
- `void invertDirection(bool invert)` - Invert motor direction
- `void invertEnable(bool invert)` - Invert enable pin logic (active LOW/HIGH)

### Power Control Methods

- `void powerOn()` - Enable motor driver
- `void powerOff()` - Disable motor driver

### Status Methods

- `long position() const` - Return current position
- `float speed() const` - Return current speed
- `float acceleration() const` - Return current acceleration setting
- `bool isMoving() const` - Returns true if motor is moving
- `bool isPoweredOn() const` - Returns true if driver is enabled

## Advanced Features

### Automatic Power Management

Enable automatic power off when the motor is idle to save energy and reduce heat:

```cpp
stepper.enableAutoOff(true);
stepper.moveAbsolute(100, 50); // Motor powers on automatically
// Motor powers off automatically when movement completes
```

### Direction and Enable Pin Inversion

For different motor driver types:

```cpp
// Invert motor direction
stepper.invertDirection(true);

// For drivers with active HIGH enable pin
stepper.invertEnable(true);
// Or set during construction
PropulsionStepper stepper(2, 3, 4, true); // invertEnable = true
```

## License

This library is released under the MIT License. See the LICENSE file for more details.
