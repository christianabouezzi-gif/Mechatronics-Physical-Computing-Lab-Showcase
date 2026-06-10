# Hygiene Dispenser

## Overview
Gesture-controlled multi-product dispensing system using APDS9960 sensor and stepper motors.

## How It Works
* Gesture input detected using APDS9960 sensor
* Microcontroller maps gestures to motor actions
* Stepper motors dispense selected product
* EEPROM stores system state

## Code

#include <Stepper.h>
#include "Adafruit_APDS9960.h"
#include <EEPROM.h>


// Define the interrupt pin
#define INT_PIN A3


// For your motor
Adafruit_APDS9960 apds;


// Change this to fit the number of steps per revolution
const int stepsPerRevolution = 2038;


// Initialize the stepper library on pins 8 through 11:
Stepper myStepper2(stepsPerRevolution, 2,4,3,5);
Stepper myStepper(stepsPerRevolution, 6,8,7,9);
Stepper myStepper3(stepsPerRevolution, 10,12,11,13);


//LED counters
int counterLEDtamp=0;
int counterLEDpad=0;
int counterLEDroll=0;


// Set max numbers of products here
int numPads=3;
int numTamps=6;
int numRoll=8;


//LED pins
const int ledPinTamp= A2;
const int ledPinPad= A5;
const int ledPinRoll=A4;

void setup() {
Serial.begin(115200);
pinMode(ledPinTamp,OUTPUT);
pinMode(ledPinRoll, OUTPUT);
pinMode(ledPinPad,OUTPUT);
pinMode(INT_PIN, INPUT_PULLUP);  // Define the INT_PIN as INPUT_PULLUP


digitalWrite(ledPinTamp, HIGH);
digitalWrite(ledPinRoll, HIGH);
digitalWrite(ledPinPad, HIGH);
// // setting LEDs on, read from past counter
// //if user turns off and on the device, check if past counters were above max, that means they refilled, so reset counters to 0
// counterLEDroll = EEPROM.read(0);
// counterLEDpad = EEPROM.read(1);
// counterLEDtamp = EEPROM.read(2);


//reset the counters
counterLEDroll=0;
counterLEDpad =0;
counterLEDtamp=0;

if(!apds.begin()){
 Serial.println("Failed to initialize device! Please check your wiring.");
} else {
 Serial.println("Device initialized!");
}


apds.enableProximity(true);
apds.enableGesture(true);
apds.setProximityInterruptThreshold(0, 175);  // Set the proximity interrupt threshold
apds.enableProximityInterrupt(); // Enable the proximity interrupt
myStepper.setSpeed(10);
myStepper2.setSpeed(10);
myStepper3.setSpeed(10);
}

void loop() {


uint8_t gesture = apds.readGesture();


// Debugging: Print gesture value
Serial.print("Gesture: ");
Serial.println(gesture);


if(gesture == APDS9960_DOWN) {
Serial.println("up gesture detected");
Serial.println("^");
counterLEDroll++;
if(counterLEDroll >=6) {
 digitalWrite(ledPinRoll, LOW); // set LED off
 }
delay(2000);
  apds.enableProximity(false);
  apds.enableGesture(false);
uint8_t prox = apds.readProximity();
while(prox!=0){
 apds.enableProximity(true);
 apds.clearInterrupt();
myStepper3.step(-100);
prox = apds.readProximity();
Serial.println(prox);
}
apds.enableGesture(true);
myStepper3.step(0);
}


// Check for gesture
if(gesture == APDS9960_LEFT) {
 Serial.println("Left gesture detected");
 counterLEDpad++; // increment
 EEPROM.write(1, counterLEDpad); // write to EEPROM to save variable
 Serial.println("<");
 myStepper2.step(-stepsPerRevolution/3);
 delay(500);
 //if(counterLEDpad >=2) {
 //  myStepper2.step((2*stepsPerRevolution)/3);
 //  digitalWrite(ledPinPad, LOW);
 //}
 }


if(gesture == APDS9960_RIGHT) {
 Serial.println("Right gesture detected");
 counterLEDtamp++; // increment
   Serial.print("Counter Tamp: ");
   Serial.print(counterLEDtamp);
 if(counterLEDtamp >=6) {
 digitalWrite(ledPinTamp, LOW); // set LED off
 }
 EEPROM.write(2, counterLEDtamp); // write to EEPROM to save variable
 Serial.println(">");
 myStepper.step(stepsPerRevolution/7);
 delay(500);
 }
}

