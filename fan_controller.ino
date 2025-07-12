/*
  Jeep XJ Fan Controller
  Author: Jesse Spyker
  Date: July 2025
  Description:
    Uses a DS18B20 temp sensor to trigger two radiator fans
    at different temperature thresholds. Fan 1 turns on at
    87°C, Fan 2 at 95°C. Readings are printed via Serial.

  Hardware:
    - Beetle CM-32U4 (DFRobot)
    - DS18B20 temperature sensor (1-wire)
    - S8050 NPN transistors (fan control)
*/


#include <OneWire.h>

// === Pin Definitions ===
int DS18S20_Pin = 16; // DS18B20 signal pin (check actual pin mapping on Beetle CM-32U4)
int F1 = 11;          // Fan 1 control pin
int F2 = 9;           // Fan 2 control pin

// === Fan Thresholds in Fahrenheit ===
float F1thresholdF = 188; // Fan 1 on at 87°C
float F2thresholdF = 203; // Fan 2 on at 95°C

// === OneWire Bus Initialization ===
OneWire ds(DS18S20_Pin);

void setup() {
  pinMode(F1, OUTPUT);
  pinMode(F2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float celsius = getTemp();

  // Reject invalid temp
  if (celsius < -100) {
    Serial.println("Sensor error or not detected.");
    delay(1000);
    return;
  }

  float fahrenheit = (celsius * 1.8) + 32;

  Serial.print("Temperature: ");
  Serial.print(celsius);
  Serial.print(" °C / ");
  Serial.print(fahrenheit);
  Serial.println(" °F");

  // === Fan Control Logic ===
  if (fahrenheit > F1thresholdF) {
    digitalWrite(F1, HIGH);
    Serial.println("Fan 1 ON");
  } else {
    digitalWrite(F1, LOW);
  }

  if (fahrenheit > F2thresholdF) {
    digitalWrite(F2, HIGH);
    Serial.println("Fan 2 ON");
  } else {
    digitalWrite(F2, LOW);
  }

  delay(1000);  // 1 second delay between readings
}

float getTemp() {
  byte data[12];
  byte addr[8];

  if (!ds.search(addr)) {
    ds.reset_search();
    return -1000;
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
    Serial.println("CRC is not valid!");
    return -1000;
  }

  if (addr[0] != 0x10 && addr[0] != 0x28) {
    Serial.println("Device not recognized");
    return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1); // Start temperature conversion

  delay(800); // Wait for conversion to complete

  ds.reset();
  ds.select(addr);
  ds.write(0xBE); // Read scratchpad

  for (int i = 0; i < 9; i++) {
    data[i] = ds.read();
  }

  ds.reset_search();

  int16_t rawTemp = (data[1] << 8) | data[0];
  float celsius = rawTemp / 16.0;

  return celsius;
}
