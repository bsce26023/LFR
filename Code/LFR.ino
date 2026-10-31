// ==========================================
// PIN DEFINITIONS
// ==========================================

// 10 Line Sensors (TCRT5000 array)
const int sensorPins[10] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9}; // Adjust pin numbers as per your MCU
int sensorValues[10];

// Motor Driver Pins (TB6612FNG)
const int PWMA = 3;  // Speed control for Motor A (Left)
const int AIN1 = 4;  // Direction 1 for Motor A
const int AIN2 = 5;  // Direction 2 for Motor A
const int PWMB = 6;  // Speed control for Motor B (Right)
const int BIN1 = 7;  // Direction 1 for Motor B
const int BIN2 = 8;  // Direction 2 for Motor B

// ==========================================
// ULTRASONIC SENSOR PINS & VARIABLES
// ==========================================
const int trigPin = 15; // Connected to Trig pin (J3 Pin 15)
const int echoPin = 14; // Connected to Echo pin (J3 Pin 14)
long duration;
int distance;
const int obstacleThreshold = 15; // Distance threshold in cm to stop/avoid obstacle

// ==========================================
// LIMIT SWITCH PIN & VARIABLES
// ==========================================
const int limitSwitchPin = 16; // Connected to SW pin (J3 Pin 16)
bool limitSwitchState = HIGH;   // Assuming pull-up configuration (LOW when pressed)

// Robot speed settings
const int baseSpeed = 180; // Max is 255

void setup() {
  // Initialize Serial Monitor for debugging
  Serial.begin(9600);

  // Initialize Line Sensors as inputs
  for (int i = 0; i < 10; i++) {
    pinMode(sensorPins[i], INPUT);
  }

  // Initialize Motor Control Pins as outputs
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  // ==========================================
  // ULTRASONIC SENSOR SETUP
  // ==========================================
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // ==========================================
  // LIMIT SWITCH SETUP
  // ==========================================
  // Using INPUT_PULLUP so the pin defaults to HIGH and goes LOW when triggered (pressed)
  pinMode(limitSwitchPin, INPUT_PULLUP);
}

void loop() {
  // ==========================================
  // 1. LIMIT SWITCH CHECK (High Priority Safety)
  // ==========================================
  // Read the state of the limit switch
  limitSwitchState = digitalRead(limitSwitchPin);
  
  // If the limit switch is pressed (assuming active LOW with INPUT_PULLUP)
  if (limitSwitchState == LOW) {
    stopMotors();
    Serial.println("SAFETY STOP: Limit switch triggered!");
    return; // Halt normal operation until reset or cleared
  }

  // ==========================================
  // 2. ULTRASONIC SENSOR CHECK (Obstacle Detection)
  // ==========================================
  // Send a 10-microsecond pulse to the Trig pin to trigger the ultrasonic burst
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the travel time of the sound wave in microseconds
  duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout (~5 meters max range)
  
  // Calculate distance in centimeters (Speed of sound is ~0.034 cm/us, divided by 2 for round trip)
  if (duration == 0) {
    distance = 999; // Out of range / no echo received
  } else {
    distance = duration * 0.034 / 2;
  }

  // Check if an obstacle is detected within the safety threshold distance
  if (distance > 0 && distance <= obstacleThreshold) {
    stopMotors();
    Serial.print("OBSTACLE DETECTED at distance: ");
    Serial.print(distance);
    Serial.println(" cm. Stopping robot.");
    return; // Pause line following while obstacle is present
  }

  // ==========================================
  // 3. 10-SENSOR LINE FOLLOWING LOGIC
  // ==========================================
  readSensors();
  executeLineFollower();
}

// Read all 10 line sensors
void readSensors() {
  for (int i = 0; i < 10; i++) {
    sensorValues[i] = digitalRead(sensorPins[i]); // Change to analogRead() if using analog thresholds
  }
}

// Basic proportional or weighted line following logic placeholder
void executeLineFollower() {
  // Example: Center sensors active -> move forward
  // Outer sensors active -> turn left or right
  // Implement your custom weighted error calculation for 10 sensors here.
  
  moveForward(baseSpeed, baseSpeed);
}

// Motor Control Helper Functions
void moveForward(int leftSpeed, int rightSpeed) {
  // Left Motor (Motor A) Forward
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, leftSpeed);

  // Right Motor (Motor B) Forward
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, rightSpeed);
}

void stopMotors() {
  // Stop both motors completely
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
}