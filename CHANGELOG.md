# Changelog

All notable changes to the PropulsionStepper library will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.1.0] - 2025-08-17

### Added
- **Automatic Power Management**: New `enableAutoOff(bool enable)` method for automatic power control
  - Motor automatically powers on when movement is requested
  - Motor automatically powers off when idle to save energy and reduce heat
  - Works with all movement methods (`moveAbsolute`, `moveRelative`, `spin`)
- **Direction Inversion**: New `invertDirection(bool invert)` method to reverse motor direction
  - Affects both physical direction and position tracking
  - Useful for different motor wiring or mechanical configurations
- **Enable Pin Inversion**: New `invertEnable(bool invert)` method and constructor option
  - Support for both active LOW (default) and active HIGH enable pins
  - New constructor: `PropulsionStepper(int stepPin, int dirPin, int enablePin, bool invertEnable)`
  - Compatible with different motor driver types
- **Position Setting**: New `setPosition(long position)` method for homing and calibration
- **Enhanced Examples**: 
  - Updated BasicUsage example with new features demonstration
  - Enhanced ContinuousRotation example with direction changes
  - New AdvancedFeatures example showcasing all capabilities

### Changed
- **Constructor Simplification**: Removed `invertDirection` parameter from constructors
  - Direction inversion now set via `invertDirection()` method only
  - Cleaner API with fewer constructor parameters
- **Updated Documentation**:
  - Comprehensive README.md update with new features and examples
  - Updated keywords.txt for Arduino IDE syntax highlighting
  - Better API organization and documentation
- **Enhanced Power Control Logic**: 
  - `powerOn()`, `powerOff()`, and `isPoweredOn()` now respect enable pin inversion
  - Improved compatibility with different motor driver types

### Removed
- **Getter Methods**: Removed unnecessary status getter methods for cleaner API
  - Removed `isDirectionInverted()` method
  - Removed `isEnableInverted()` method  
  - Removed `isAutoOffEnabled()` method
- **Constructor Parameters**: Removed `invertDirection` parameters from constructors

### Technical Details
- All new features are backward compatible
- Default behavior unchanged (no inversions, manual power control)
- Enable pin inversion properly handled in constructor initialization
- AutoOff feature integrates seamlessly with existing movement methods

### Examples
```cpp
// New automatic power management
stepper.enableAutoOff(true);
stepper.moveAbsolute(200, 100); // Powers on automatically

// New direction inversion
stepper.invertDirection(true);

// New enable pin inversion (constructor)
PropulsionStepper stepper(2, 3, 4, true); // invertEnable = true

// New enable pin inversion (method)
stepper.invertEnable(true);
```

## [1.0.3] - 2025-08-17

### Fixed
- **PlatformIO Compatibility**: Updated `library.json` for better PlatformIO support
  - Fixed framework specification from architecture names to "arduino"
  - Updated platform names to PlatformIO standard format
  - Added proper export configuration for header file discovery
  - Extended platform support for better compatibility

### Changed
- **Platform Support**: Extended compatibility to more Arduino-compatible platforms
  - Added support for STM32, Nordic nRF52, Raspberry Pi Pico, and Teensy platforms
  - Better platform specification in `library.json`

## [1.0.2] - 2025-08-16

### Initial Release
- Basic stepper motor control with acceleration and deceleration
- Support for absolute and relative positioning
- Continuous rotation capability
- Speed and acceleration control
- Power management (manual on/off)
- Support for 2-pin (step/dir) and 3-pin (step/dir/enable) motor drivers
- Arduino IDE and PlatformIO compatibility
