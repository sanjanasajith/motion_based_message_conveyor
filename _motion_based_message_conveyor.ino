#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <LiquidCrystal.h>
#define handleTiltRequest
// Create objects for the sensor and LCD
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345); //
Replace with your sensor's I2C address if needed
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
const int ledPins[4] = {8, 9, 10, 11}; // Array for LED pins
int xVal, yVal;
// Define the pin for the buzzer
#define BUZZER_PIN 13
void setup() {
lcd.begin(16, 2);
Serial.begin(9600);
// Initialize all LED pins as outputs
for (int i = 0; i < 4; i++) {
pinMode(ledPins[i], OUTPUT);
digitalWrite(ledPins[i], HIGH); // Turn all LEDs on initially (optional)
}
// Initialize the buzzer pin as an output
pinMode(BUZZER_PIN, OUTPUT);
if (!accel.begin()) {
Serial.println("Check MEMS sensor initialization failed!");
while (1); // Halt if initialization fails
}
accel.setRange(ADXL345_RANGE_16_G); // Set sensor range (adjust if
needed) 
Serial.println("Welcome");
delay(2000);
lcd.print("MSG CONVEYOR FOR");
lcd.setCursor(0, 1);
 lcd.print("PARALYTIC PERSON");
 delay(1500);
}
void loop() {
 lcd.clear();
 sensors_event_t event;
 accel.getEvent(&event);
 xVal = event.acceleration.x;
 yVal = event.acceleration.y;
 Serial.print("X: ");
 Serial.print(xVal);
 Serial.print(" Y: ");
 Serial.print(yVal);
Serial.println();
delay(500); // Adjust delay as needed
 // Improved logic for message detection
 if (isFrontTilt(xVal, yVal)) { // Forward tilt (Need water)
 handleTiltRequest("Need water", ledPins[0], 1000);
 } else if (isRightTilt(xVal, yVal)) { // Right tilt (Need food)
 handleTiltRequest("Need food", ledPins[1], 2000);
 } else if (isLeftTilt(xVal, yVal)) { // Left tilt (Need medicine)
 handleTiltRequest("Need medical support", ledPins[2], 3000);
 } else if (isBackTilt(xVal, yVal)) { // Back tilt (Need to use restroom)
 handleTiltRequest("Need to use restroom", ledPins[3], 4000);
 } else {
 // Handle cases where the values don't fall into any specific range
 Serial.println("Unrecognized tilt");
 // Optionally display an "unrecognized message" on the LCD
 }
} 
// Function to check for front tilt
bool isFrontTilt(int xVal, int yVal) {
 return (xVal > -2 && xVal < 4) && (yVal > -11 && yVal < 4);
}
// Function to check for right tilt
bool isRightTilt(int xVal, int yVal) {
 return (xVal > 3 && xVal < 11) && (yVal > -6 && yVal < 4);
}
// Function to check for left tilt
bool isLeftTilt(int xVal, int yVal) {
 return (xVal > -11 && xVal < -5) && (yVal > -4 && yVal < 3);
}
// Function to check for back tilt
bool isBackTilt(int xVal, int yVal) {
 // Adjust thresholds for back tilt based on sensor sensitivity and mounting angle
 return (xVal > -8 && xVal < 2) && (yVal < -7 && yVal > -12);
}  