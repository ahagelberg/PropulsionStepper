#include <PropulsionStepper.h>

const int stepPin = 3; // Pin connected to the step pin of the motor driver
const int dirPin = 4;  // Pin connected to the direction pin of the motor driver
const int enablePin = 5; // Pin connected to the enable pin of the motor driver (optional)

PropulsionStepper stepper(stepPin, dirPin, enablePin);

void setup() {
    stepper.setAcceleration(100.0); // Set acceleration
    stepper.spin(50.0); // Start continuous rotation at speed 50
}

void loop() {
    // Allow the motor to keep rotating
    stepper.loop(); // Call the loop method to update motor state
}
