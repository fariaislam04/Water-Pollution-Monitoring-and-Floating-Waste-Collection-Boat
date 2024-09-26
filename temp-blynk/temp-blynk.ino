#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6znMymr2u"
#define BLYNK_TEMPLATE_NAME "Temperature and TDS Monitor"
#define BLYNK_AUTH_TOKEN "o1qgSCawGVWQDMOWjtTv0v-TfJmzL5Xg"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// TDS sensor related definitions
#define TdsSensorPin 27    // Pin where the TDS sensor is connected
#define VREF 3.3           // Analog reference voltage of the ESP32 (3.3V)
#define SCOUNT  30         // Number of samples for TDS

// DS18B20 sensor related definitions
const int oneWireBus = 15;  // Pin where the DS18B20 is connected

// Turbidity sensor pin definition
#define TurbiditySensorPin 35  // Pin where the Turbidity sensor is connected

OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "MIST";  
char pass[] = "Il0veMIST";      

BlynkTimer timer;

int analogBuffer[SCOUNT];   // Buffer to store ADC values for TDS
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0;
float averageVoltage = 0, tdsValue = 0, temperature = 25;

// Function to get median value
float getMedianNum(int bArray[], int iFilterLen) {
  int bTab[iFilterLen];
  for (int i = 0; i < iFilterLen; i++) bTab[i] = bArray[i];
  for (int i = 0; i < iFilterLen - 1; i++) {
    for (int j = 0; j < iFilterLen - i - 1; j++) {
      if (bTab[j] > bTab[j + 1]) {
        int temp = bTab[j];
        bTab[j] = bTab[j + 1];
        bTab[j + 1] = temp;
      }
    }
  }
  return (iFilterLen & 1) ? bTab[(iFilterLen - 1) / 2] : (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
}

// Function to read and send TDS value
void sendTDS() {
  static unsigned long analogSampleTime = millis();
  if (millis() - analogSampleTime > 40) {  // Every 40ms, read TDS sensor data
    analogSampleTime = millis();
    analogBuffer[analogBufferIndex++] = analogRead(TdsSensorPin);
    if (analogBufferIndex == SCOUNT) analogBufferIndex = 0;
  }

  for (int copyIndex = 0; copyIndex < SCOUNT; copyIndex++) {
    analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
  }
  
  averageVoltage = getMedianNum(analogBufferTemp, SCOUNT) * (float)VREF / 4096.0;  // Calculate average voltage
  float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0); // Temperature compensation formula
  float compensationVoltage = averageVoltage / compensationCoefficient;
  tdsValue = (133.42 * compensationVoltage * compensationVoltage * compensationVoltage 
              - 255.86 * compensationVoltage * compensationVoltage 
              + 857.39 * compensationVoltage) * 0.5;

  Serial.print("TDS Value: ");
  Serial.print(tdsValue, 0);
  Serial.println("ppm");

  Blynk.virtualWrite(V2, tdsValue);  // Send TDS value to Blynk Virtual Pin V2
}

// Function to read and send temperature
void sendTemperature() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.println("ºC");

  if (tempC != DEVICE_DISCONNECTED_C) {
    temperature = tempC;  // Update the global temperature for TDS compensation
    Blynk.virtualWrite(V0, tempC);  // Send temperature to Blynk Virtual Pin V3
  } else {
    Serial.println("Error: Could not read temperature data");
  }
}

// Function to read and send turbidity value
void sendTurbidity() {
  int turbidityValue = analogRead(TurbiditySensorPin);  // Read the turbidity sensor data
  float voltage = turbidityValue * (VREF / 4096.0);    // Convert the ADC value to voltage
  float turbidityNTU = -1120.4 * voltage * voltage + 5742.3 * voltage - 4352.9;  // Convert voltage to NTU (calibrated formula)

  // Add condition for turbidity levels
  if (turbidityNTU < 20) {
    Serial.println("Clear");
    Blynk.virtualWrite(V4, "Clear");  // Send status to Blynk Virtual Pin V5
  } 
  else if (turbidityNTU >= 20 && turbidityNTU < 50) {
    Serial.println("Cloudy");
    Blynk.virtualWrite(V4, "Cloudy");  // Send status to Blynk Virtual Pin V5
  } 
  else if (turbidityNTU >= 50) {
    Serial.println("Dirty");
    Blynk.virtualWrite(V4, "Dirty");  // Send status to Blynk Virtual Pin V5
  }

 
}

void setup() {
  Serial.begin(115200);
  
  sensors.begin();  // Initialize the DS18B20 sensor

  Blynk.begin(auth, ssid, pass);  // Connect to Blynk
  
  timer.setInterval(1000L, sendTemperature);  // Read and send temperature every 1 second
  timer.setInterval(1000L, sendTDS);          // Read and send TDS every 1 second
  timer.setInterval(1000L, sendTurbidity);    // Read and send turbidity every 1 second
}

void loop() {
  Blynk.run();
  timer.run();
}
