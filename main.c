#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// Define analog pins for flex sensors
const int flexThumbPin = A0;
const int flexIndexPin = A1;
const int flexMiddlePin = A2;
const int flexRingPin = A3;
const int flexPinkyPin = A4;

// Flex sensor thresholds (calibrate for your setup)
const int flexThreshold = 400;

// Variables to hold sensor data
int flexThumbVal, flexIndexVal, flexMiddleVal, flexRingVal, flexPinkyVal;
int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {
  Serial.begin(115200);

  // Initialize MPU6050
  Wire.begin();
  mpu.initialize();
  
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  } else {
    Serial.println("MPU6050 connection successful");
  }
}

void loop() {
  // Read flex sensor values
  flexThumbVal = analogRead(flexThumbPin);
  flexIndexVal = analogRead(flexIndexPin);
  flexMiddleVal = analogRead(flexMiddlePin);
  flexRingVal = analogRead(flexRingPin);
  flexPinkyVal = analogRead(flexPinkyPin);

  // Read IMU data
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Process flex sensor data and determine hand shape
  String handShape = detectHandShape();

  // Display hand shape and orientation
  Serial.print("Hand Shape: ");
  Serial.println(handShape);

  Serial.print("Orientation (ax, ay, az): ");
  Serial.print(ax); Serial.print(", ");
  Serial.print(ay); Serial.print(", ");
  Serial.println(az);

  delay(500);  // Adjust based on how often you want to refresh
}

String detectHandShape() {
  String shape = "";

  if (flexThumbVal > flexThreshold) {
    shape += "Thumb Bent, ";
  } else {
    shape += "Thumb Straight, ";
  }

  if (flexIndexVal > flexThreshold) {
    shape += "Index Bent, ";
  } else {
    shape += "Index Straight, ";
  }

  if (flexMiddleVal > flexThreshold) {
    shape += "Middle Bent, ";
  } else {
    shape += "Middle Straight, ";
  }

  if (flexRingVal > flexThreshold) {
    shape += "Ring Bent, ";
  } else {
    shape += "Ring Straight, ";
  }

  if (flexPinkyVal > flexThreshold) {
    shape += "Pinky Bent";
  } else {
    shape += "Pinky Straight";
  }

  return shape;
}
