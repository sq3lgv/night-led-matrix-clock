#include "EnvSensor.h"
#include "DebugMacros.h"

void EnvSensor::initialize(){
  
  pinMode(PHOTORESISTOR_PIN, INPUT);

  Wire.begin();
}

TemperatureAndHumidity EnvSensor::readTemperatureAndHumidity(){
    dht.begin();
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (!(isnan(h) || isnan(t))) {
      DEBUG_PRINT("\nHUM:", (int)h);
      DEBUG_PRINT("\nTEMP:", (int)(t * 10));
    } else {
      DEBUG_PRINTS("\nFailed to read temp\n");
    }

    return TemperatureAndHumidity(t, h);
}

LightIntensity EnvSensor::readLightIntensity(){
  int value = analogRead(A0);
  DEBUG_PRINT("\nANALOG: ", value);
  return LightIntensity(value);
}