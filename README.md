<h1 align="center">Methane and Hydrogen Gas Sensor System</h1>
<h3 align="center">Arduino-Based Gas Detection Prototype</h3>

---

## Overview

This project presents a low-cost gas detection system capable of detecting methane (<b>CH₄</b>) and hydrogen (<b>H₂</b>) using MQ-series gas sensors interfaced with an Arduino Uno.

The objective of this project was to develop a practical prototype for detecting highly flammable gases in laboratory and industrial environments using affordable embedded hardware.

The system uses:

<ul>
  <li>MQ-4 sensor for methane detection</li>
  <li>MQ-8 sensor for hydrogen detection</li>
  <li>Arduino Uno (ATmega328P) for signal acquisition and processing</li>
  <li>Real-time serial monitoring through Arduino IDE</li>
</ul>

The sensor output is converted from analog voltage into estimated gas concentration (PPM) using sensor characteristic equations derived from datasheet response curves.

---

## Problem Statement

Detection of combustible gases such as methane and hydrogen is critical for industrial safety, laboratory monitoring, and leak detection systems.

Commercial gas analyzers are expensive, while low-cost sensor-based solutions often suffer from calibration and environmental limitations.

This project explores the development of a budget-friendly gas monitoring prototype using MQ sensors and microcontroller-based signal processing.

---

## Hardware Components

<table>
<tr>
<th>Component</th>
<th>Purpose</th>
</tr>

<tr>
<td>Arduino Uno</td>
<td>Main microcontroller</td>
</tr>

<tr>
<td>MQ-4 Gas Sensor</td>
<td>Methane detection</td>
</tr>

<tr>
<td>MQ-8 Gas Sensor</td>
<td>Hydrogen detection</td>
</tr>

<tr>
<td>Breadboard</td>
<td>Circuit prototyping</td>
</tr>

<tr>
<td>Jumper Wires</td>
<td>Electrical connections</td>
</tr>

<tr>
<td>Medical One-Way Valve Syringe</td>
<td>Controlled gas injection</td>
</tr>

<tr>
<td>Latex Balloons</td>
<td>Improvised gas chamber</td>
</tr>

<tr>
<td>Regulated Gas Source</td>
<td>Methane / Hydrogen supply</td>
</tr>

<tr>
<td>Arduino IDE</td>
<td>Serial monitoring and data logging</td>
</tr>

</table>

---

## Experimental Design

Due to the unavailability of a sealed gas chamber with a known volume, an improvised experimental setup was developed for controlled gas testing.

### Methodology

<b>Reference Balloon:</b>

<ul>
<li>Contained ambient air</li>
<li>Contained MQ gas sensor (MQ-4 or MQ-8)</li>
</ul>

<b>Source Balloon:</b>

<ul>
<li>Contained target gas (Methane / Hydrogen)</li>
</ul>

A <b>medical one-way valve syringe</b> was used to transfer controlled gas volumes from the source balloon into the reference balloon.

This approach enabled gradual gas concentration increase while minimizing gas backflow and leakage.

---
<p align="center">
  <img src="images/setup" width="45%">
</p>

## Experimental Workflow

<ol>
<li>Preheat the gas sensor for stabilization</li>
<li>Calibrate the sensor in clean ambient air</li>
<li>Determine baseline resistance (<b>R<sub>o</sub></b>)</li>
<li>Inject a controlled volume of target gas</li>
<li>Read analog sensor output</li>
<li>Convert ADC reading into output voltage</li>
<li>Calculate sensing resistance (<b>R<sub>s</sub></b>)</li>
<li>Compute resistance ratio (<b>R<sub>s</sub>/R<sub>o</sub></b>)</li>
<li>Estimate gas concentration in PPM</li>
<li>Log readings using Arduino Serial Monitor</li>
</ol>

---

## Quantitative Model

### Sensor Output Voltage

$$
V_{out} = ADC \times \frac{V_c}{1023}
$$

Where:

<ul>
<li><b>V<sub>out</sub></b> = Sensor output voltage</li>
<li><b>ADC</b> = Analog reading (0–1023)</li>
<li><b>V<sub>c</sub></b> = Supply voltage</li>
</ul>

### Sensor Resistance

$$
R_s = R_L \left(\frac{V_c}{V_{out}} - 1\right)
$$

### Gas Concentration Estimation

$$
PPM = \left(\frac{R_s/R_o}{A}\right)^{1/B}
$$

Calibration constants:

**MQ-4 (Methane)**

$$
A = 4.4,\quad B = -0.38
$$

**MQ-8 (Hydrogen)**

$$
A = 0.42,\quad B = -0.48
$$

---

## Working Principle

<ul>
<li>In clean air, the sensor establishes baseline resistance (<b>R<sub>o</sub></b>)</li>
<li>Exposure to methane or hydrogen changes sensor resistance</li>
<li>Sensor resistance (<b>R<sub>s</sub></b>) decreases with gas concentration</li>
<li>The ratio <b>R<sub>s</sub>/R<sub>o</sub></b> is used to estimate gas concentration</li>
<li>Gas concentration is computed in PPM using empirical calibration equations</li>
</ul>

---

<p align="center">
  <img src="images/gas_injection1" width="45%">
</p>
<p align="center">
  <img src="images/gas_injection2" width="45%">
</p>
<p align="center">
  <img src="images/gas_injection3" width="45%">
</p>
<p align="center">
  <img src="images/image4" width="45%">
</p>

## Results

Observed behavior matched expected MQ sensor characteristics:

<ul>
<li>Increasing methane concentration reduced sensor resistance</li>
<li>Increasing hydrogen concentration reduced sensor resistance</li>
<li>Log-log response approximately followed datasheet trends</li>
</ul>

Example methane range observed:

$$
67\ \text{ppm} \rightarrow 512\ \text{ppm}
$$

---

## Limitations

<ul>
<li>Arduino Uno uses only 10-bit ADC</li>
<li>Limited measurement precision</li>
<li>No sealed calibration chamber</li>
<li>Environmental factors affect readings</li>
<li>MQ sensors are not perfectly selective</li>
<li>Datasheet-based approximation introduces error</li>
</ul>

---

## Proposed Improvements

<ul>
<li>ESP32 integration</li>
<li>ADS1115 16-bit external ADC</li>
<li>Closed acrylic / 3D printed gas chamber</li>
<li>DHT22 temperature-humidity compensation</li>
<li>OLED display</li>
<li>Buzzer-based alarm</li>
<li>Cloud logging via WiFi</li>
</ul>
