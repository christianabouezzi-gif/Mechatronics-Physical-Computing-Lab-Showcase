#include <Stepper.h>
#include "Adafruit_APDS9960.h"
#include <EEPROM.h>

// Interrupt pin for gesture sensor
#define INT_PIN A3

Adafruit_APDS9960 apds;

// Stepper motor configuration
const int stepsPerRevolution = 2038;

Stepper stepperPad(stepsPerRevolution, 2, 4, 3, 5);
Stepper stepperTamp(stepsPerRevolution, 6, 8, 7, 9);
Stepper stepperRoll(stepsPerRevolution, 10, 12, 11, 13);

// Counters for each product
int counterTamp = 0;
int counterPad = 0;
int counterRoll = 0;

// Maximum usage thresholds
int maxPads = 3;
int maxTamps = 6;
int maxRoll = 8;

//for the pins
const int ledTamp = A2;
const int ledPad  = A5;
const int ledRoll = A4;


void setup() {
  Serial.begin(115200);

  pinMode(ledTamp, OUTPUT);
  pinMode(ledPad, OUTPUT);
  pinMode(ledRoll, OUTPUT);
  pinMode(INT_PIN, INPUT_PULLUP);

  // Turn LEDs ON initially
  digitalWrite(ledTamp, HIGH);
  digitalWrite(ledPad, HIGH);
  digitalWrite(ledRoll, HIGH);

  // Reset counters (you can replace with EEPROM restore if needed)
  counterRoll = 0;
  counterPad = 0;
  counterTamp = 0;

  // Initialize APDS9960 sensor
  if (!apds.begin()) {
    Serial.println("APDS9960 initialization failed!");
    while (1);
  } else {
    Serial.println("APDS9960 initialized successfully.");
  }

  // Enable sensor features
  apds.enableProximity(true);
  apds.enableGesture(true);
  apds.setProximityInterruptThreshold(0, 175);
  apds.enableProximityInterrupt();

  // Set stepper speed
  stepperPad.setSpeed(10);
  stepperTamp.setSpeed(10);
  stepperRoll.setSpeed(10);
}

void loop() {

  uint8_t gesture = apds.readGesture();

  Serial.print("Gesture: ");
  Serial.println(gesture);

  //Down gesture
  if (gesture == APDS9960_DOWN) {

    Serial.println("Down gesture detected (Roll)");

    counterRoll++;

    if (counterRoll >= maxRoll) {
      digitalWrite(ledRoll, LOW);
    }

    delay(2000);

    apds.enableProximity(false);
    apds.enableGesture(false);

    uint8_t prox = apds.readProximity();

   //checks proximity
    while (prox != 0) {
      apds.enableProximity(true);
      apds.clearInterrupt();

      stepperRoll.step(-100);

      prox = apds.readProximity();
      Serial.println(prox);
    }

    apds.enableGesture(true);
    stepperRoll.step(0);
  }

  //left gesture
  if (gesture == APDS9960_LEFT) {

    Serial.println("Left gesture detected (Pad)");

    counterPad++;
    EEPROM.write(1, counterPad);

    stepperPad.step(-stepsPerRevolution / 3);

    delay(500);
  }

  //right gesture
  if (gesture == APDS9960_RIGHT) {

    Serial.println("Right gesture detected (Tampon)");

    counterTamp++;

    if (counterTamp >= maxTamps) {
      digitalWrite(ledTamp, LOW);
    }

    EEPROM.write(2, counterTamp);

    stepperTamp.step(stepsPerRevolution / 7);

    delay(500);
  }
}
