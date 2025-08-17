#include <PropulsionStepper.h>

const int stepPin = 3; // Pin connected to the step pin of the motor driver
const int dirPin = 4;  // Pin connected to the direction pin of the motor driver
const int enablePin = 5; // Pin connected to the enable pin of the motor driver (optional)

// Example using constructor with enable pin inversion for active HIGH drivers
// PropulsionStepper stepper(stepPin, dirPin, enablePin, true);

PropulsionStepper stepper(stepPin, dirPin, enablePin);

void setup() {
    Serial.begin(9600);
    
    // Configure stepper motor
    stepper.setAcceleration(50.0);  // Set acceleration to 50 steps/s²
    stepper.enableAutoOff(true);    // Enable automatic power management
    
    // Uncomment if your motor direction is reversed
    // stepper.invertDirection(true);
    
    Serial.println("Starting continuous rotation...");
    Serial.println("Motor will change direction every 5 seconds");
    
    stepper.spin(100.0); // Start continuous rotation at speed 100 steps/s
}

void loop() {
    stepper.loop(); // IMPORTANT: Call this regularly to update motor state
    
    // Change direction every 5 seconds
    static unsigned long lastDirectionChange = 0;
    static bool clockwise = true;
    
    if (millis() - lastDirectionChange > 5000) {
        clockwise = !clockwise;
        float newSpeed = clockwise ? 100.0 : -100.0;
        
        Serial.print("Changing direction to: ");
        Serial.println(clockwise ? "Clockwise" : "Counter-clockwise");
        
        stepper.spin(newSpeed);
        lastDirectionChange = millis();
    }
}
