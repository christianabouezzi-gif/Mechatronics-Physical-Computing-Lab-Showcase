
# Mechatronics-Physical-Computing-Lab-Showcase

This repository contains three engineering projects focused on embedded systems, structural analysis, and product design. The work demonstrates experience in MATLAB programming, microcontroller development, sensor integration, and engineering design.

## Project Overview

This repository includes

1. Hygiene Dispenser – A gesture-controlled dispensing system using sensors and stepper motors.
2. Truss Analysis & Failure Prediction – A MATLAB-based structural analysis tool for calculating forces and predicting failure in truss structures.
3. Digital Thermometer – An Arduino-based temperature monitoring system with real-time display and alerts.

## Hygiene Dispenser

A gesture-controlled hygiene dispenser designed to deliver multiple products using sensor-based user input and automated mechanical actuation.

<img width="512" height="355" alt="unnamed-3" src="https://github.com/user-attachments/assets/968265f1-e833-4607-af0e-e8c11fbc575c" />


### Key Features

* Gesture-based input using APDS9960 sensor
* Multi-product dispensing system (pads, tampons, toilet paper)
* Stepper motor actuation for controlled mechanical output
* EEPROM-based memory for state persistence
* Proximity-based safety override for user protection

### Methodology & Code Structure
* APDS9960 gesture sensor detects directional swipes (left, right, up, down)
* Microcontroller maps gestures to specific stepper motor movements
* Each gesture triggers a controlled rotation of the dispensing mechanism
* Proximity sensor disables gesture input when hand is too close
* EEPROM is used to retain system state during power interruptions

### Results 
* Successfully translates gesture inputs into reliable mechanical output
* Consistent dispensing performance during extended testing
* Requires stable 5V power supply (2A recommended) for full torque operation
* Installation limited to locations with accessible power sources

### Technologies Used
* Arduino
* C++
* APDS9960 Gesture Sensor
* Stepper Motors
* EEPROM


## Truss Analysis & Failure Prediction

A MATLAB-based structural analysis project used to evaluate a 15-member truss system and predict structural failure under load.

<img width="1237" height="775" alt="bridge" src="https://github.com/user-attachments/assets/e90e91e1-a555-4ce7-9d23-b9be32c600f5" />


### Key Features

* Static equilibrium-based force analysis
* 15-member truss modeling system
* Buckling and failure prediction calculations
* Geometry optimization under physical constraints
* Load distribution analysis


### Methodology
* MATLAB model generates truss geometry and applies load conditions
* Forces are calculated using structural equilibrium equations
* Buckling limits are computed for each member
* Optimization loop adjusts geometry for improved load distribution
* Critical members are identified based on failure thresholds

### Results 

* Member 7 identified as the critical failure point (61.26 oz predicted buckling load)
* Member 8 identified as a high-risk secondary failure element
* Final design improves load distribution through geometric adjustment
* Demonstrates strong correlation between member length and failure risk

### Technologies Used
* MATLAB
* Structural Analysis
* Buckling Theory
* Numerical Optimization

## Digital Thermometer
An Arduino-based temperature monitoring system that measures ambient temperature and provides real-time visual and audio feedback.

<img width="512" height="372" alt="unnamed-2" src="https://github.com/user-attachments/assets/211e46dd-6366-4a72-9794-fcc98178d4c9" />

### Key Features

* Real-time temperature monitoring
* Dual output in Celsius and Fahrenheit
* LED status indicators (normal and alert conditions)
* Audio alert system using buzzer
* LCD display for live temperature updates

### Methodology 
* TMP36 temperature sensor reads analog voltage values
* Microcontroller converts readings into temperature values
* System continuously compares readings against safety thresholds
* LCD updates in real time with current temperature
* Buzzer and LED activate when temperature exceeds limits


### Results

* Reliable real-time temperature tracking
* Successful activation of alerts during threshold breaches
* Stable performance under continuous operation
* Battery-powered operation requires power optimization for long-term use

### Technologies Used

* Arduino
* TMP36 Temperature Sensor
* LCD Display (I2C)
* C++
* Buzzer and LED Systems

## Author
Christian Abou-Ezzi
