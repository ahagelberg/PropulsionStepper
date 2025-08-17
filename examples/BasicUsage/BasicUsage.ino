#include <PropulsionStepper.h>

const int stepPin = 3; // Pin connected to the step pin of the motor driver
const int dirPin = 4;  // Pin connected to the direction pin of the motor driver
const int enablePin = 5; // Pin connected to the enable pin of the motor driver (optional)

PropulsionStepper stepper(stepPin, dirPin, enablePin);

void setup() {
    Serial.begin(9600); // Initialize serial communication
    
    // Configure stepper motor
    stepper.setAcceleration(100.0); // Set acceleration to 100 steps/s²
    stepper.enableAutoOff(true);    // Enable automatic power management
    
    // Uncomment if your motor direction is reversed
    // stepper.invertDirection(true);
    
    // Uncomment if your driver uses active HIGH enable pin
    // stepper.invertEnable(true);
    
    Serial.println("Starting stepper motor test...");
    stepper.moveAbsolute(200, 100.0); // Move to absolute position 200 at speed 100
}

void loop() {
    stepper.loop(); // IMPORTANT: Call this regularly to update motor state
    
    if (!stepper.isMoving()) {
        Serial.print("Movement complete! Current position: ");
        Serial.println(stepper.position());
        delay(1000); // Wait for a second before the next command
        
        // Move back to starting position
        stepper.moveRelative(-200, 100.0);
    }
}