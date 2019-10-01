#include "Adafruit_BME680.h"

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME680 bme; // I2C

void initBME680() {
  //myDelay(10);
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");

  } else {
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150); // 320*C for 150 ms
    Serial.println("Initialized BME680");
  }
}


void readBME680() {
  if (! bme.performReading()) {
    Serial.println("Failed to perform reading BME680 :(");
    return;
  }
  Serial.print("Temperature = ");
  sensors.measurement[0] = String(bme.temperature);
  Serial.print(sensors.measurement[0]);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  sensors.measurement[1] = String(bme.pressure / 100.0);
  Serial.print(sensors.measurement[1]);
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  sensors.measurement[2] = String(bme.humidity);
  Serial.print(sensors.measurement[2]);
  Serial.println(" %");

  Serial.print("Gas = ");
  sensors.measurement[3] = String(bme.gas_resistance / 1000.0);
  Serial.print(sensors.measurement[3]);
  Serial.println(" KOhms");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  //String header[] = {"Temp", "Preasure", "Humidity", "Gas", "Light", "Volt", "PIR","Radar","Audio"};
  //String value[]  = { "0"  , "1",        "2",        "3",   "4"    , "5",    "6",   "7",   "8"    };

}

