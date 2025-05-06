#include <PropulsionStepper.h>

const int stepPin = 3; // Pin connected to the step pin of the motor driver
const int dirPin = 4;  // Pin connected to the direction pin of the motor driver
const int enablePin = 5; // Pin connected to the enable pin of the motor driver (optional)

PropulsionStepper stepper(stepPin, dirPin, enablePin);

void setup() {
    Serial.begin(9600); // Initialize serial communication
    stepper.setAcceleration(100.0); // Set acceleration
    stepper.moveAbsolute(200, 100.0); // Move to absolute position 200 at speed 100
}

void loop() {
    if (!stepper.isMoving()) {
        Serial.println("Movement complete!");
        delay(1000); // Wait for a second before the next command
        stepper.moveRelative(-200, 100.0); // Move back to the starting position
    }
    stepper.loop(); // Call the loop method to update motor state
}