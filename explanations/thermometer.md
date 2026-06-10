# Digital Thermometer (Arduino)

## Overview
This project is a digital thermometer built using an Arduino and an analog temperature sensor (TMP36 or similar). It measures ambient temperature in real time by reading an analog voltage signal, converting it into temperature units, and displaying the result via Serial Monitor or an LCD screen.

The project demonstrates analog-to-digital conversion, calibration of sensor data, and real-time embedded system monitoring.

---

## Key Features
- Real-time temperature measurement  
- Analog sensor input via ADC  
- Conversion from voltage to temperature (°C / °F)  
- Serial or LCD output display  
- Continuous live updating system  

---

## Hardware Required
- Arduino Uno  
- TMP36 temperature sensor (or equivalent analog sensor)  
- LCD display (optional, I2C recommended)  
- Jumper wires  
- Breadboard  
- USB or external 5V power supply  

---

## Pin Mapping

### Temperature Sensor
| Component | Pin |
|----------|-----|
| TMP36 Output | A0 |
| VCC | 5V |
| GND | GND |

---

### LCD (Optional)
| Component | Pin |
|----------|-----|
| SDA | A4 |
| SCL | A5 |

---

## How It Works

### Analog Reading
The sensor outputs a voltage proportional to temperature:
- TMP36 baseline: 0.5V at 0°C  
- Scale factor: 10 mV per °C  

Arduino reads this using ADC:
- Converts analog voltage into a digital value (0–1023)

---

### Voltage Conversion
Voltage = analogRead(A0) * (5.0 / 1023.0)
---

### Temperature Conversion (TMP36)
Temperature (°C) = (Voltage - 0.5) * 100


---

### Output Display
The final temperature value is displayed via:
- Serial Monitor, or  
- LCD screen (real-time updates)

---

## System Behavior
- Continuously updates inside `loop()`  
- Small delay added for stability  
- Slight noise in readings is normal for analog sensors  
- Can be improved using averaging or filtering  
