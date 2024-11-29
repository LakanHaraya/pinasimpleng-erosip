/*
  Isang joystik at apat na servo motor sa PCA9685

  Tuluyang magpiprint sa erial monitor kahit walang pagbabago sa input ng joystick
*/

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PWMServoDriver.h>

// Constants for servo motor angles
#define SERVO_MIN 150  // Min pulse length out of 4096
#define SERVO_MAX 600  // Max pulse length out of 4096

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

// Timing variables
const unsigned long UPDATE_INTERVAL = 10; // Update every 20ms
unsigned long lastUpdateTime = 0;

void setup() {
  Serial.begin(115200);
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
}

void loop() {
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

    // Calculate averaged values
    int averagedRudder = rudderTotal / NUM_READINGS;
    int averagedElevator = elevatorTotal / NUM_READINGS;

    // Map averaged joystick values to servo pulse lengths
    int rudderPulse = map(averagedRudder, 0, 1023, SERVO_MIN, SERVO_MAX);
    int elevatorPulse = map(averagedElevator, 0, 1023, SERVO_MIN, SERVO_MAX);

    // Set servo positions
    pwm.setPWM(RUDDER1, 0, rudderPulse);
    pwm.setPWM(RUDDER2, 0, rudderPulse);
    pwm.setPWM(ELEVATOR1, 0, elevatorPulse);
    pwm.setPWM(ELEVATOR2, 0, elevatorPulse);

    // Optional: Print debug info
    Serial.print("Rudder Pulse: ");
    Serial.print(rudderPulse);
    Serial.print(" Elevator Pulse: ");
    Serial.println(elevatorPulse);
  }
}
