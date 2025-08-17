#include <PropulsionStepper.h>

const int stepPin = 3; // Pin connected to the step pin of the motor driver
const int dirPin = 4;  // Pin connected to the direction pin of the motor driver
const int enablePin = 5; // Pin connected to the enable pin of the motor driver

// Example: Create stepper with inverted enable pin (for active HIGH drivers)
// PropulsionStepper stepper(stepPin, dirPin, enablePin, true);

PropulsionStepper stepper(stepPin, dirPin, enablePin);

void setup() {
    Serial.begin(9600);
    Serial.println("PropulsionStepper Advanced Features Demo");
    Serial.println("========================================");
    
    // Configure stepper motor
    stepper.setAcceleration(200.0);  // High acceleration for demonstration
    stepper.enableAutoOff(true);     // Enable automatic power management
    
    // Demonstrate direction inversion
    Serial.println("Testing normal direction...");
    stepper.moveRelative(100, 150.0);
    
    while (stepper.isMoving()) {
        stepper.loop();
        delay(10);
    }
    
    Serial.println("Inverting direction and moving same relative amount...");
    stepper.invertDirection(true);   // Invert direction
    stepper.moveRelative(100, 150.0); // Should move opposite direction
    
    while (stepper.isMoving()) {
        stepper.loop();
        delay(10);
    }
    
    // Reset direction and position
    stepper.invertDirection(false);
    stepper.setPosition(0); // Reset position counter
    
    Serial.println("Advanced features demo completed!");
    Serial.println("Starting continuous operation...");
}

void loop() {
    stepper.loop(); // IMPORTANT: Always call this in loop()
    
    static unsigned long lastAction = 0;
    static int step = 0;
    
    if (millis() - lastAction > 3000 && !stepper.isMoving()) {
        
        switch (step % 4) {
            case 0:
                Serial.println("Moving to position 200...");
                stepper.moveAbsolute(200, 100.0);
                break;
                
            case 1:
                Serial.println("Spinning clockwise...");
                stepper.spin(80.0);
                break;
                
            case 2:
                Serial.println("Stopping and moving to position -100...");
                stepper.stop();
                delay(500);
                stepper.moveAbsolute(-100, 120.0);
                break;
                
            case 3:
                Serial.println("Spinning counter-clockwise...");
                stepper.spin(-60.0);
                break;
        }
        
        step++;
        lastAction = millis();
        
        // Print status
        Serial.print("Current position: ");
        Serial.print(stepper.position());
        Serial.print(", Speed: ");
        Serial.print(stepper.speed());
        Serial.print(", Powered: ");
        Serial.println(stepper.isPoweredOn() ? "ON" : "OFF");
    }
}
