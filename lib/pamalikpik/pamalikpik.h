#ifndef PAMALIKPIK_H
#define PAMALIKPIK_H

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

// Constants for servo motor angles
#define SERVO_MIN 150  // Min pulse length out of 4096
#define SERVO_MAX 600  // Max pulse length out of 4096

// Joystick pins
extern const int JRX1; // Joystick Right X-axis
extern const int JRY1; // Joystick Right Y-axis

// Servo channels on PCA9685
extern const int RUDDER1;
extern const int RUDDER2;
extern const int ELEVATOR1;
extern const int ELEVATOR2;

// Constants for smoothing
extern const int NUM_READINGS;
extern int rudderReadings[];
extern int elevatorReadings[];
extern int rudderIndex;
extern int elevatorIndex;
extern int rudderTotal;
extern int elevatorTotal;

// Constants for idle detection
extern const int IDLE_THRESHOLD; // Minimum change to consider movement

// Constants for servo angle limits
extern const int RUDDER_MIN_ANGLE;
extern const int RUDDER_MAX_ANGLE;
extern const int ELEVATOR_MIN_ANGLE;
extern const int ELEVATOR_MAX_ANGLE;

// Timing variables
extern const unsigned long UPDATE_INTERVAL; // Update every 10ms
extern unsigned long lastUpdateTime;

// Idle flag
extern bool idlePrinted;

// Function prototypes
void initRudderElevator();
void updateRudderElevator();
void printDebugInfo(int rudderInput, int elevatorInput, const char* status);

#endif // PAMALIKPIK_H
