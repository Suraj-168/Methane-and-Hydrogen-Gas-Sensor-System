# Methane-and-Hydrogen-Gas-Sensor-System

Overview

This project presents a low-cost gas detection system capable of detecting methane (CH₄) and hydrogen (H₂) using MQ-series gas sensors interfaced with an Arduino Uno.

The objective of this project was to develop a practical prototype for detecting highly flammable gases in laboratory and industrial environments using affordable embedded hardware.

The system uses:

MQ-4 sensor for methane detection
MQ-8 sensor for hydrogen detection
Arduino Uno (ATmega328P) for signal acquisition and processing
Real-time serial monitoring through Arduino IDE

The sensor output is converted from analog voltage into estimated gas concentration (PPM) using sensor characteristic equations derived from datasheet response curves.

Problem Statement:

Detection of combustible gases such as methane and hydrogen is critical for industrial safety, laboratory monitoring, and leak detection systems.
Commercial gas analyzers are expensive, while low-cost sensor-based solutions often suffer from calibration and environmental limitations.
This project explores the development of a budget-friendly gas monitoring prototype using MQ sensors and microcontroller-based signal processing.

| Component                     | Purpose                            |
| ----------------------------- | ---------------------------------- |
| Arduino Uno                   | Main microcontroller               |
| MQ-4 Gas Sensor               | Methane detection                  |
| MQ-8 Gas Sensor               | Hydrogen detection                 |
| Breadboard                    | Circuit prototyping                |
| Jumper Wires                  | Electrical connections             |
| Medical One-Way Valve Syringe | Controlled gas injection           |
| Latex Balloons                | Improvised gas chamber             |
| Regulated Gas Source          | Methane / Hydrogen supply          |
| Arduino IDE                   | Serial monitoring and data logging |



Experimental Design

Due to the unavailability of a sealed gas chamber with known volume, an improvised experimental setup was developed.

Methodology
Two balloons were used:
Reference Balloon
Contained:
Ambient air
Gas sensor (MQ-4 or MQ-8)

Source Balloon
Contained:
Target gas (Methane / Hydrogen)

A medical one-way valve syringe was used to transfer controlled gas volumes from the source balloon into the reference balloon.

This setup allowed gradual concentration increase while minimizing gas backflow.


Experimental Workflow
-Preheat sensor for stabilization
-Calibrate sensor in clean air
-Measure baseline resistance (Ro)
-Inject controlled gas volume
-Read analog sensor output
-Convert ADC reading → voltage
-Calculate sensor resistance (Rs)
-Compute Rs/Ro ratio
-Estimate gas concentration in PPM
-Log readings in serial monitor


## Quantitative Model

The gas sensor output is converted into gas concentration using the following mathematical model.

### 1. Sensor Output Voltage

The analog reading from the Arduino ADC is converted into output voltage:

$$
V_{out} = ADC \times \frac{V_c}{1023}
$$

Where:

- $V_{out}$ = Sensor output voltage
- $ADC$ = Analog reading from Arduino (0–1023)
- $V_c$ = Supply voltage (5V)

---

### 2. Sensor Resistance Calculation

The sensing resistance is calculated using the voltage divider equation:

$$
R_s = R_L \left( \frac{V_c}{V_{out}} - 1 \right)
$$

Where:

- $R_s$ = Sensor resistance
- $R_L$ = Load resistance
- $V_c$ = Supply voltage
- $V_{out}$ = Sensor output voltage

---

### 3. Gas Concentration Estimation

The gas concentration in parts per million (PPM) is estimated using the empirical sensor model:

$$
PPM = \left( \frac{R_s / R_o}{A} \right)^{1/B}
$$

Where:

- $R_s$ = Sensor resistance in target gas
- $R_o$ = Sensor resistance in clean air
- $R_s/R_o$ = Sensor resistance ratio
- $A, B$ = Sensor calibration constants from datasheet curve fitting

---

### Calibration Constants

For different sensors:

**MQ-4 (Methane):**

$$
A = 4.4,\quad B = -0.38
$$

**MQ-8 (Hydrogen):**

$$
A = 0.42,\quad B = -0.48
$$

---

### Working Principle

- In clean air, the sensor establishes a baseline resistance ($R_o$).
- When methane or hydrogen gas is introduced, the sensing material reacts with gas molecules.
- This causes the sensor resistance ($R_s$) to decrease.
- The ratio $R_s/R_o$ changes according to gas concentration.
- Using the fitted mathematical model, gas concentration is estimated in PPM.


Results:

Observed behavior matched expected MQ sensor characteristics:

-Increasing methane concentration reduced sensor resistance

-Increasing hydrogen concentration reduced sensor resistance

-Log-log response approximately followed datasheet trend

Example methane range observed:

67 ppm → 512 ppm

Limitations

Current prototype has several limitations:

-Arduino Uno uses only 10-bit ADC (1024 steps)

-Limited measurement precision

-No sealed calibration chamber

-Environmental factors (temperature/humidity) affect readings

-MQ sensors are not perfectly selective

-Gas concentration estimation depends on datasheet approximation



Proposed Improvements

Future enhancements include:

-ESP32 integration

-ADS1115 16-bit external ADC

-Closed acrylic / 3D printed test chamber

-DHT22 temperature-humidity compensation

-OLED display for standalone monitoring

-Buzzer-based leak alarm

-Cloud logging via WiFi

