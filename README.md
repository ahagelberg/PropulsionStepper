# PropulsionStepper Library

The `PropulsionStepper` library provides an easy-to-use interface for controlling stepper motors with Arduino. It allows for precise movement to absolute or relative positions, speed and acceleration management, as well as continuous rotation.

## Features

- Move to absolute or relative positions
- Continuous movement
- Set speed and acceleration
- Control power states (on/off)

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

PropulsionStepper stepper(stepPin, dirPin);

void setup() {
    stepper.setAcceleration(100.0);
    stepper.moveAbsolute(200, 50.0); // Move to position 200 at speed 50
}

void loop() {
    stepper.loop(); // Call loop to update motor state
}
```

## API Reference

### Constructor

- `PropulsionStepper(int stepPin, int dirPin, int enablePin)`
- `PropulsionStepper(int stepPin, int dirPin)`

### Methods

- `void moveAbsolute(long targetPosition, float speed)` - Move to absolute position
- `void moveRelative(long steps, float speed)` - Move relative to current position
- `void spin(float speed)` - Continuous rotation at set speed (steps/s^2)
- `void stop()` - Stop motion immediately (no deceleration). To stop with deceleration use spin(0).
- `void powerOn()` - Enable motor driver (assumes active LOW signal)
- `void powerOff()` - Disable motor driver (assumes active LOW signal)
- `float speed() const` - Set top speed for relative and absolute motion
- `long position() const` - Return current position
- `bool isMoving() const` - Returns true if motor is moving
- `bool isPoweredOn() const` - Retuns true if driver is enabled
- `void setAcceleration(float acceleration)` - Sets the acceleration in steps/s^2

## License

This library is released under the MIT License. See the LICENSE file for more details.
