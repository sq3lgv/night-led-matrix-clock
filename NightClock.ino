#include "LowPower.h"
#include "DebugMacros.h"
#include "RTClock.h"
#include "EnvSensor.h"
#include "LedMatrixClockDisplay.h"



LedMatrixClockDisplay display;
EnvSensor sensor;
RTClock rtClock;

void setup() {
  DEBUG_INITIALIZE();
  DEBUG_PRINTS("\nNight Clock\n");

  sensor.initialize();
  display.initialize();
}


void loop() {
   LightIntensity lightValue = sensor.readLightIntensity();

  if (lightValue.isDark()) {
    display.startup();

    RTime time = rtClock.readTime();

    TemperatureAndHumidity thValue = sensor.readTemperatureAndHumidity();

    display.clear();
    display.print(time);

    if (thValue.isValid()){
      display.print(thValue);
    }

  } else {
    display.shutdown();
  }

  display.update();

  DEBUG_FLUSH();
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}
