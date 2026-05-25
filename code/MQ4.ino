#define MQ4_PIN A0          // MQ-4 analog output pin
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

// Function to estimate methane concentration (PPM)
float calculateMethanePPM(float ratio) {
  // Approximate MQ-4 methane curve constants
  float A = 4.4;
  float B = -0.38;

  float ppm = pow((ratio / A), (1.0 / B));
  return ppm;
}

// Sensor calibration in clean air
void calibrateSensor() {
  Serial.println("Calibrating MQ-4 sensor in clean air...");
  Serial.println("Please keep the sensor in fresh ambient air.");

  float rsSum = 0;
  int samples = 100;

  for (int i = 0; i < samples; i++) {
    int adcValue = analogRead(MQ4_PIN);
    float Rs = calculateRs(adcValue);
    rsSum += Rs;
    delay(200);
  }

  float RsAvg = rsSum / samples;

  // Clean air factor for MQ-4
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
  Serial.println("MQ-4 Methane Gas Detection System");
  Serial.println("================================");

  delay(5000); // Sensor warm-up time

  calibrateSensor();
}

void loop() {
  if (!calibrated) return;

  int adcValue = analogRead(MQ4_PIN);

  float Rs = calculateRs(adcValue);
  float ratio = Rs / Ro;
  float methanePPM = calculateMethanePPM(ratio);

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

  Serial.print("Methane Level   : ");
  Serial.print(methanePPM);
  Serial.println(" PPM");

  Serial.println("-----------------------------------");

  delay(1000);
}
