#define MQ8_PIN A0          // MQ-8 analog output pin
#define RL 1.0              // Load resistance in kΩ
#define VC 5.0              // Supply voltage
#define ADC_RES 1023.0      // 10-bit ADC resolution

float Ro = 0;               // Clean air resistance
bool calibrated = false;

// Function to calculate sensor resistance (Rs)
float calculateRs(int adcValue) {
  float Vout = adcValue * (VC / ADC_RES);

  if (Vout <= 0.01) {
    return 999999; // Prevent division by zero
  }

  float Rs = RL * ((VC / Vout) - 1.0);
  return Rs;
}

// Function to estimate hydrogen concentration (PPM)
float calculateHydrogenPPM(float ratio) {
  // Approximate MQ-8 hydrogen curve constants
  float A = 0.42;
  float B = -0.48;

  float ppm = pow((ratio / A), (1.0 / B));
  return ppm;
}

// Sensor calibration in clean air
void calibrateSensor() {
  Serial.println("Calibrating MQ-8 sensor in clean air...");
  Serial.println("Please keep the sensor in fresh ambient air.");

  float rsSum = 0;
  int samples = 100;

  for (int i = 0; i < samples; i++) {
    int adcValue = analogRead(MQ8_PIN);
    float Rs = calculateRs(adcValue);
    rsSum += Rs;
    delay(200);
  }

  float RsAvg = rsSum / samples;

  // Clean air factor for MQ-8
  Ro = RsAvg / 4.4;

  Serial.println("--------------------------------");
  Serial.print("Calibration complete. Ro = ");
  Serial.print(Ro);
  Serial.println(" kΩ");
  Serial.println("--------------------------------");

  calibrated = true;
}

void setup() {
  Serial.begin(9600);

  Serial.println("================================");
  Serial.println("MQ-8 Hydrogen Gas Detection System");
  Serial.println("================================");

  delay(5000); // Sensor warm-up

  calibrateSensor();
}

void loop() {
  if (!calibrated) return;

  int adcValue = analogRead(MQ8_PIN);

  float Rs = calculateRs(adcValue);
  float ratio = Rs / Ro;
  float hydrogenPPM = calculateHydrogenPPM(ratio);

  Serial.println("----------- Sensor Data -----------");

  Serial.print("ADC Value       : ");
  Serial.println(adcValue);

  Serial.print("Sensor Voltage  : ");
  Serial.print(adcValue * (VC / ADC_RES));
  Serial.println(" V");

  Serial.print("Rs              : ");
  Serial.print(Rs);
  Serial.println(" kΩ");

  Serial.print("Rs/Ro Ratio     : ");
  Serial.println(ratio);

  Serial.print("Hydrogen Level  : ");
  Serial.print(hydrogenPPM);
  Serial.println(" PPM");

  Serial.println("-----------------------------------");

  delay(1000);
}
