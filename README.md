# Mechatronics-Physical-Computing-Lab-Showcase

This repository contains three engineering projects that demonstrate experience in product design, structural analysis, embedded systems, CAD modeling, and engineering documentation. The projects were completed as part of coursework and design-focused engineering projects.

Three distinct projects are included:

1. Hygiene Dispenser: A touch-free dispensing system designed with a focus on usability, manufacturability, and hygiene.
2. Truss Analysis & Failure Prediction: A MATLAB-based structural analysis tool used to evaluate truss member forces and identify potential failure locations.
3. Digital Thermometer: A temperature measurement system integrating sensors, electronics, and digital output for real-time monitoring.

# Hygiene Dispenser

A gesture-controlled smart dispenser designed around an advanced sensor layout to distribute a variety of hygiene products. The system relies on precise mechanical motion and an integrated micro-controller to determine proper item release based on physical hand motions.

# Key Features

The device leverages an array of hardware and software components to deliver reliable tactile operation:
* Gesture Interactivity: An embedded sensor processes structural proximity measurements and tracks directional user signals.
* Multi-Product Mechanics: The architecture utilizes a set of independent mechanical motor lines to physically push outward three
target items: pads, tampons, and toilet paper.
* System Toggles: Includes an active tracking switch loop to seamlessly disconnect the internal logic from the active power grid 
during servicing.

# Methodology & Code Structure
* Sensor Logic Implementation: The primary tracking loop queries the active register values of the onboard APDS9960 gesture sensor to catch vector directions (e.g., APDS9960_DOWN or APDS9960_LEFT).
* Dynamic Step Calculation: Upon identifying a directional swipe, the micro-controller calculates precise fraction rotations (-stepsPerRevolution/3) mapped directly onto corresponding stepper channels (myStepper2.step) to move the hardware mechanism.
* Variable State Management: The codebase utilizes integrated EEPROM non-volatile storage (EEPROM.write) to back up and persist active counting metrics across sudden power interruptions.
* Proximity Overrides: An asynchronous sub-routine samples raw proximity readings (apds.readProximity()) to temporarily disable primary gesture tracking while real-time structural clearance is established.
