#pragma once
#include <Wire.h>
#include "DHT.h"

#define PHOTORESISTOR_PIN A0
#define DHT_PIN 7       
#define DHT_TYPE DHT22

class TemperatureAndHumidity {
public:
  inline float getTemperature() {return temperature;}
  inline float getHumidity() {return humidity; }
  inline bool isValid(){ return !isnan(temperature) && !isnan(humidity); }
  inline TemperatureAndHumidity(float temperature, float humidity) {
    this->temperature = temperature;
    this->humidity = humidity;
  }
private:
  float temperature;
  float humidity;
};

class LightIntensity{
public:
  inline bool isDark(){ return value > 700; }

  inline LightIntensity(int value) {
    this->value = value;
  }
private:
  int value;
};

class EnvSensor {
public:
  void initialize();

  TemperatureAndHumidity readTemperatureAndHumidity();
  LightIntensity readLightIntensity();

private:
  DHT dht = DHT(DHT_PIN, DHT_TYPE);
};
