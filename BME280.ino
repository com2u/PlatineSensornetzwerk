#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <BME280I2C.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

//Adafruit_BME280 bme280t; // I2C
BME280I2C bme280t;     
boolean BME280OK = false;

void initBME280() {
  //myDelay(10);
  if (!bme280t.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    BME280OK = false;

  } else {
    Serial.println("Initialized BME280");
    BME280OK = true;
  }
}


void readBME280() {
  if (!BME280OK) {
    Serial.println("Failed to perform reading BME280 :(");
    return;
  }

float temp(NAN), hum(NAN), pres(NAN);
   uint8_t pressureUnit(3);   // unit: B000 = Pa, B001 = hPa, B010 = Hg, B011 = atm, B100 = bar, B101 = torr, B110 = N/m^2, B111 = psi
   bool metric = false;
   bme280t.read(pres, temp, hum, metric, pressureUnit);                   // Parameters: (float& pressure, float& temp, float& humidity, bool celsius = false, uint8_t pressureUnit = 0x0)
  sensors.measurement[0] = String(temp);
  sensors.measurement[1] = String(pres);
  sensors.measurement[2] = String(hum);
    
  Serial.print("Temperature = ");
  //sensors.measurement[0] = String(bme280t.readTemperature());
  Serial.print(sensors.measurement[0]);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  //sensors.measurement[1] = String(bme280t.readPressure() / 100.0F);
  Serial.print(sensors.measurement[1]);
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  //sensors.measurement[2] = String(bme280t.readHumidity());
  Serial.print(sensors.measurement[2]);
  Serial.println(" %");

 

  //String header[] = {"Temp", "Preasure", "Humidity", "Gas", "Light", "Volt", "PIR","Radar","Audio"};
  //String value[]  = { "0"  , "1",        "2",        "3",   "4"    , "5",    "6",   "7",   "8"    };

}

