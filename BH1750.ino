#include <BH1750FVI.h>

// Create the Lightsensor instance
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);

void initBH1750() 
{
  LightSensor.begin();  
}

void readBH1750()
{
  uint16_t lux = LightSensor.GetLightIntensity();
  Serial.print("Light: ");
  sensors.measurement[4] = String(lux);
  Serial.println(sensors.measurement[4]);
  
  

}
