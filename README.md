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

# Results & Key Findings
* Operational Performance: Through repeated operational stress testing over twelve weeks, the multi-gesture tracking framework successfully translated localized vector swipes into individual product releases.
* Power Limitations: Evaluation metrics indicated that the stepper lines require a substantial 5V 2A continuous wall outlet profile to maintain necessary torque levels.
* Placement Restrictions: Relying strictly on a standard AC main transformer introduces physical placement restrictions, confining the practical installation zones exclusively to areas near available bathroom wall outlets.

# Truss Analysis & Failure Prediction

A structural engineering design project centered around building and testing a structural framework (Truss) optimized for load tolerance. The project combines analytical mathematical calculations in MATLAB with physical prototyping constraints to maximize load efficiency against budget caps.

# Key Features

* Structural Material Budgeting: Optimization of total component lengths to prevent exceeding a fixed, mandatory project cost ceiling.
* Dimensional Boundaries: Adherence to strict element span regulations requiring all structural members to remain within a specific 7 to 14-inch physical range.
* Analytical Vector Tracing: Automated tracking equations mapped directly across a 15-member structural coordinate space to differentiate structural parts under load.

# Methodology & Code Structure
* Parametric MATLAB Adjustments: The engineering process involved executing an analytical program loop in MATLAB, altering structural coordinates piece by piece to identify the ideal spatial layout.
* Force Proportionality Modeling: An automated algorithm mapped structural element force limits relative to a total applied system mass $(W_{fail})$ using individual component constants (R) inside the equation $$Length=R⋅W_{fail}$$.
* Buckling Tolerance Calculations: Compressive resistance thresholds were calculated across every structural element via the power equation $$W = 3054.789 \cdot L^{-2.009}$$ to pinpoint immediate failure zones based on length (L).
* Structural Geometry Balancing: The final design introduced a rounded upper profile to distribute localized pressure vectors more uniformly away from solitary critical peaks.
# Results & Key Findings

* Critical Buckling Peak: Member 7 (a 7-inch piece) was identified as the absolute critical member, exhibiting a precise calculated local buckling threshold of 61.26 oz.
* Uncertainty Bounds: Risk analysis highlighted Member 8 as a highly volatile element whose lower structural tolerance bound (+/- 1.36 oz) places it directly in danger of early failure before Member 7 under load.

# Digital Thermometer
An Arduino-driven climate monitoring system designed to provide real-time alerts when ambient temperatures drift out of a designated homeostatic zone. The device provides immediate sensory notification via integrated visual, audio, and text readouts.

#Key Features

* Dual Thermal Scaling: Internal computational routines parse a single sensor channel to output active conditions in both Celsius and Fahrenheit simultaneously.
* Acoustic Background Stream: An ongoing multi-note background loop plays a continuous musical track throughout active sampling cycles.
* Multi-Stage Visual Indicators: An integrated configuration utilizes a continuous green LED for power status and a flashing red LED for extreme thermal boundary alerts.

# Methodology & Code Structure
* Signal Capture & Interpolation: The micro-controller samples an analog pin (analogRead(tmp)) tied to a TMP36 thermal IC, converting raw voltage levels directly into a metric index via calibrated formulas (voltage / 1024.0).
* Dynamic Boundary Testing: An active comparative check loop (if (tempF < 68 || tempF > 75)) continuously tests ambient metrics against safe upper and lower boundaries.
* Asynchronous Note Synthesis: A specialized buzzer routine interprets nested arrays of pitch values (melody[note]) and relative durations (1000 / durations[note]) to synthesize clear acoustic frequencies using precise delay gates.
* I2C Display Communication: Data strings are sent through dedicated signal lines to update an alphanumeric 16x2 LCD panel (lcd.print(tempF)) every time the alert tune finishes.

# Results & Key Findings

* Alert Execution: The prototype successfully executes real-time emergency beeps and red LED strobes whenever temperatures breach the safe operational baseline.
* Power Management Constraints: The circuit draws its power from a 9V battery source through a built-in step-down transformer block, requiring careful consideration of power longevity during remote operations.
* Hardware Limitations: Evaluation notes indicated that the 16x2 LCD backlight requires precise mounting positions inside the custom enclosure lid to ensure readability during active room testing.
