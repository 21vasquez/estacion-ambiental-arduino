#include <Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_AHTX0.h>

// HC-05: Pin 10 = RX del Arduino (al TXD del HC-05)
//        Pin 11 = TX del Arduino (al RXD del HC-05 con divisor de voltaje)
SoftwareSerial BT(10, 11);

// Sensores analógicos
const int PIN_LUZ = A0;  // TEMT6000
const int PIN_GAS = A1;  // MQ-135

// Sensor I2C AHT20 (A4 = SDA, A5 = SCL)
Adafruit_AHTX0 aht;
bool ahtOk = false;

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  ahtOk = aht.begin();
}

void loop() {
  // 1. TEMT6000 (Luz en porcentaje)
  int luzRaw = analogRead(PIN_LUZ);
  float luzPorc = (luzRaw / 1023.0) * 100.0;

  // 2. MQ-135 (Calidad de aire, valor crudo 0-1023)
  int gasRaw = analogRead(PIN_GAS);

  // 3. AHT20 (Temperatura y Humedad)
  float temp = 0.0;
  float hum = 0.0;
  if (ahtOk) {
    sensors_event_t humedadEv, tempEv;
    aht.getEvent(&humedadEv, &tempEv);
    temp = tempEv.temperature;
    hum = humedadEv.relative_humidity;
  }

  // Envío por Bluetooth en formato CSV: Temp,Hum,Luz,Aire
  BT.print(temp, 1);    BT.print(",");
  BT.print(hum, 1);     BT.print(",");
  BT.print(luzPorc, 0); BT.print(",");
  BT.println(gasRaw);

  // Copia por USB para monitoreo local
  Serial.print(temp, 1);    Serial.print(",");
  Serial.print(hum, 1);     Serial.print(",");
  Serial.print(luzPorc, 0); Serial.print(",");
  Serial.println(gasRaw);

  delay(2000);
}
