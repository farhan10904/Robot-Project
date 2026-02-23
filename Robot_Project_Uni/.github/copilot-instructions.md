# Copilot Instructions for Robot Project

## Project Overview
This is an Arduino-based autonomous robot that follows lines using IR sensors and delivers packages using ultrasonic detection and a stepper motor. The system uses a state machine (FollowLine, LostLine, ApproachDropoff, DeliverPackage) to manage behavior.

## Architecture
- **Main Entry**: `Robot_Project_Uni.ino` - Contains the main loop with plate detection and delivery logic
- **Components**:
  - `Sensors.ino/h`: IR line sensors (L/C/R) and ultrasonic distance measurement
  - `Motors.ino/h`: DC motor control for movement and stepper motor for package delivery
  - `Line_Following.ino/h`: PID-like speed computation based on sensor readings
  - `Config.ino`: All constants, pin definitions, and global state variables
  - `Types.h`: Enums for Action and State

## Key Patterns
- **Shared State**: Use `extern` declarations in headers for global variables defined in `Config.ino` (e.g., `CurrentState`, `SimMode`)
- **Simulation Mode**: Set `SimMode = true` in `Config.ino` for testing without hardware; sensors return simulated values
- **Sensor Readings**: Line sensors return 1 for line detected (active level defined in config), ultrasonic returns distance in cm
- **Motor Control**: Speeds range -255 to 255; positive for forward, negative for reverse
- **Package Delivery**: Uses stepper motor with `StepsPerRevolution` and `StepDelay` for precise rotation

## Development Workflow
- **Testing**: Upload individual test files (`MotorTest.ino`, `SensorTest.ino`, `ProximitySensotTest.ino`) to verify components
- **Debugging**: Use `Serial.println()` for output; simulation mode prints motor speeds instead of setting pins
- **Configuration**: Modify constants in `Config.ino` for tuning (e.g., `base` speed, `turnL/R` adjustments, `PlateDistanceThreshold`)
- **State Transitions**: Follow the logic in main loop: detect plates → approach → deliver → cooldown → resume line following

## Common Tasks
- **Add New Sensor**: Define pins in `Config.ino`, add setup in `SensorSetup()`, implement reading function in `Sensors.ino`
- **Tune Line Following**: Adjust `base`, `turnL`, `turnR` in `Config.ino` based on sensor feedback
- **Modify Delivery**: Change `StepsPerRevolution` or add logic in `PackageDelivery()` for different mechanisms

## Examples
- To detect a plate: `if (DistanceToPlate(TriggerFront, ReceiveFront) <= PlateDistanceThreshold)`
- To set motors: `SetMotorSpeed(150, 150)` for forward at base speed
- To transition state: `CurrentState = DeliverPackage;` then call `PackageDelivery()`</content>
<parameter name="filePath">c:\Users\mfa15\Project\Robot-Project\Robot_Project_Uni\.github\copilot-instructions.md