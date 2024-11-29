#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PWMServoDriver.h>
#include "pamalikpik.h"

// Create PCA9685 object
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Joystick pins
const int JRX1 = A0; // Joystick Right X-axis
const int JRY1 = A1; // Joystick Right Y-axis

// Servo channels on PCA9685
const int RUDDER1 = 0;
const int RUDDER2 = 4;
const int ELEVATOR1 = 8;
const int ELEVATOR2 = 12;

// Constants for smoothing
const int NUM_READINGS = 10; // Number of readings for averaging
int rudderReadings[NUM_READINGS] = {0};
int elevatorReadings[NUM_READINGS] = {0};
int rudderIndex = 0;
int elevatorIndex = 0;
int rudderTotal = 0;
int elevatorTotal = 0;

// Constants for idle detection
const int IDLE_THRESHOLD = 5; // Minimum change to consider movement

// Constants for servo angle limits
const int RUDDER_MIN_ANGLE = 10;
const int RUDDER_MAX_ANGLE = 170;
const int ELEVATOR_MIN_ANGLE = 20;
const int ELEVATOR_MAX_ANGLE = 160;

// Timing variables
const unsigned long UPDATE_INTERVAL = 10; // Update every 10ms
unsigned long lastUpdateTime = 0;

// Idle flag
bool idlePrinted = false;

// Initialize rudder and elevator system
void initRudderElevator() {
  pwm.begin();
  pwm.setPWMFreq(60); // Analog servos run at ~60 Hz

  pinMode(JRX1, INPUT);
  pinMode(JRY1, INPUT);

  // Initialize smoothing arrays
  for (int i = 0; i < NUM_READINGS; i++) {
    rudderReadings[i] = analogRead(JRX1);
    elevatorReadings[i] = analogRead(JRY1);
    rudderTotal += rudderReadings[i];
    elevatorTotal += elevatorReadings[i];
  }

  // Print the header line
  Serial.println(": JRX1 : JRY1 : PLPK :");
}

// Update rudder and elevator based on joystick input
void updateRudderElevator() {
  unsigned long currentTime = millis();

  // Only update at defined intervals
  if (currentTime - lastUpdateTime >= UPDATE_INTERVAL) {
    lastUpdateTime = currentTime;

    // Read joystick values
    int rudderInput = analogRead(JRX1);
    int elevatorInput = analogRead(JRY1);

    // Update smoothing arrays
    rudderTotal = rudderTotal - rudderReadings[rudderIndex] + rudderInput;
    elevatorTotal = elevatorTotal - elevatorReadings[elevatorIndex] + elevatorInput;

    rudderReadings[rudderIndex] = rudderInput;
    elevatorReadings[elevatorIndex] = elevatorInput;

    rudderIndex = (rudderIndex + 1) % NUM_READINGS;
    elevatorIndex = (elevatorIndex + 1) % NUM_READINGS;

    int averagedRudder = rudderTotal / NUM_READINGS;
    int averagedElevator = elevatorTotal / NUM_READINGS;

    // Calculate changes in input
    static int lastRudder = averagedRudder;
    static int lastElevator = averagedElevator;
    int rudderChange = abs(averagedRudder - lastRudder);
    int elevatorChange = abs(averagedElevator - lastElevator);

    // Only update servos if movement exceeds threshold
    if (rudderChange > IDLE_THRESHOLD || elevatorChange > IDLE_THRESHOLD) {
      // Map averaged joystick values to servo pulse lengths
      int rudderPulse = map(averagedRudder, 0, 1023, SERVO_MIN, SERVO_MAX);
      int elevatorPulse = map(averagedElevator, 0, 1023, SERVO_MIN, SERVO_MAX);

      // Constrain servo pulses to specified limits
      rudderPulse = constrain(rudderPulse, map(RUDDER_MIN_ANGLE, 0, 180, SERVO_MIN, SERVO_MAX), map(RUDDER_MAX_ANGLE, 0, 180, SERVO_MIN, SERVO_MAX));
      elevatorPulse = constrain(elevatorPulse, map(ELEVATOR_MIN_ANGLE, 0, 180, SERVO_MIN, SERVO_MAX), map(ELEVATOR_MAX_ANGLE, 0, 180, SERVO_MIN, SERVO_MAX));

      // Set servo positions
      pwm.setPWM(RUDDER1, 0, rudderPulse);
      pwm.setPWM(RUDDER2, 0, rudderPulse);
      pwm.setPWM(ELEVATOR1, 0, elevatorPulse);
      pwm.setPWM(ELEVATOR2, 0, elevatorPulse);

      // Print debug info for changes using the function
      printDebugInfo(rudderInput, elevatorInput, "MOVG");

      // Reset idle flag
      idlePrinted = false;

    } else {
      // Print "Idle" status only once when no significant change
      if (!idlePrinted) {
        // Print idle status along with current rudder and elevator pulse values
        printDebugInfo(lastRudder, lastElevator, "IDLE");

        idlePrinted = true;  // Set flag to avoid repeated printing
      }
    }

    // Update last known positions
    lastRudder = averagedRudder;
    lastElevator = averagedElevator;
  }
}

// Function for printing debug info
void printDebugInfo(int rudderInput, int elevatorInput, const char* status) {
  // Format: JRX1 : JRY1 : PLPK
  Serial.print(": ");
  Serial.print(rudderInput);
  Serial.print(" : ");
  Serial.print(elevatorInput);
  Serial.print(" : ");
  Serial.println(status);
}