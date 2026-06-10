# Gesture-Controlled Hygiene Dispenser (Arduino)

## Overview
This project is a gesture-controlled dispensing system built with an Arduino and an APDS9960 gesture sensor. It controls three stepper motors to dispense different hygiene products (pads, tampons, and toilet paper rolls) based on user hand gestures. The system also tracks usage counts and disables product indicators when limits are reached.

---

## Features
- Gesture-based control using APDS9960 sensor
- Controls 3 stepper motors independently
- Tracks usage counts for each product:
  - Pads
  - Tampons
  - Toilet paper rolls
- Uses EEPROM storage to retain counts (partial implementation)
- LED indicators show product availability
- Automatic stop mechanism when max usage is reached
- Proximity-based safety stop for roll dispensing

---

## Hardware Required
- Arduino Uno
- APDS9960 gesture & proximity sensor
- 3× Stepper motors (28BYJ-48 or equivalent)
- ULN2003 driver boards (for steppers)
- 3× LEDs (status indicators)
- Jumper wires
- External 5V power supply (recommended for motors)

---

## Pin Mapping

### LEDs

| Component | Pin |
|----------|-----|
| Tampon LED | A2 |
| Pad LED | A5 |
| Roll LED | A4 |

---

### Gesture Sensor

| Component | Pin |
|----------|-----|
| Interrupt | A3 |
| I2C | SDA/SCL (default Arduino pins) |

---

### Stepper Motors

| Motor | Pins |
|------|------|
| Pad | 2, 4, 3, 5 |
| Tampon | 6, 8, 7, 9 |
| Roll | 10, 12, 11, 13 |

---

## Libraries Used
Install in Arduino IDE:

- `Stepper.h` – controls stepper motors  
- `Adafruit_APDS9960.h` – gesture/proximity sensor  
- `EEPROM.h` – non-volatile memory storage  

---

## Gesture Mapping

| Gesture | Action | Product |
|--------|--------|---------|
| DOWN/PROXIMITY | Dispense roll | Toilet paper |
| LEFT | Dispense pad | Pads |
| RIGHT | Dispense tampon | Tampons |

---

## How It Works

### Initialization
- Initializes APDS9960 sensor  
- Sets up stepper motors  
- Turns LEDs ON (available state)  
- Initializes counters  

### Gesture Detection
- `uint8_t gesture = apds.readGesture()`-;

## Roll Dispensing (DOWN)
- Uses proximity detection  
- Motor runs until object is gone  
- Auto safety stop  

---

## Pad Dispensing (LEFT)
- Rotates motor 1/3 revolution  
- Increments counter  
- Saves to EEPROM  

---

## Tampon Dispensing (RIGHT)
- Rotates motor 1/7 revolution  
- Increments counter  
- Turns LED OFF at max capacity  

---

## EEPROM Usage
- `counterPad → address 1`  
- `counterTamp → address 2`  

---

## System Behavior
- Pads max: 3 uses  
- Tampons max: 6 uses  
- Rolls max: 8 uses  
- Stepper speed: 10 RPM  
- 2s delay added after roll gesture  
 
