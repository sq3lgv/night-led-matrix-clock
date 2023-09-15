#include "LowPower.h"
#include "DHT.h"

#include <DS3231.h>
#include <Wire.h>
#include <MD_MAX72xx.h>

// Turn on debug statements to the serial output
#define DEBUG 1

#if DEBUG
#define PRINT(s, x) \
  { \
    Serial.print(F(s)); \
    Serial.print(x); \
  }
#define PRINTS(x) Serial.print(F(x))
#define PRINTD(x) Serial.println(x, DEC)

#else
#define PRINT(s, x)
#define PRINTS(x)
#define PRINTD(x)

#endif

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::ICSTATION_HW
#define MAX_DEVICES 16

#define CLK_PIN 13   // or SCK
#define DATA_PIN 11  // or MOSI
#define CS_PIN 10    // or SS

#define DHTPIN 7       // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22  // DHT 22  (AM2302), AM2321

// SPI hardware interface
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
DS3231 myRTC;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
#if DEBUG
  Serial.begin(57600);
#endif
  PRINTS("\n[MD_MAX72XX Test & Demo]");

  if (!mx.begin())
    PRINTS("\nMD_MAX72XX initialization failed");


  mx.control(MD_MAX72XX::INTENSITY, 0);
  // mx.control(MD_MAX72XX::INTENSITY, 8);
  mx.update(MD_MAX72XX::OFF);
  pinMode(A0, INPUT);
  
  Wire.begin();

  // myRTC.setClockMode(false);
  //       myRTC.setHour(22);
  //       myRTC.setMinute(54);
  //       myRTC.setSecond(0);
}


void display_time_example2() {
  uint8_t zero[160] = {
    0b00000000,
    0b00000000,
    0b00111100,
    0b01111110,
    0b11100111,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11100111,
    0b01111110,
    0b00111100,
    0b00000000,
    0b00000000,

    0b00000000,
    0b00000000,
    0b00001100,
    0b00011100,
    0b00111100,
    0b00111100,
    0b00001100,
    0b00001100,
    0b00001100,
    0b00001100,
    0b00001100,
    0b00001100,
    0b00001100,
    0b00001100,
    0b00000000,
    0b00000000,

    0b00000000,
    0b00000000,
    0b00111100,
    0b01111110,
    0b11100111,
    0b11000111,
    0b00000111,
    0b00001110,
    0b00011100,
    0b00111000,
    0b01110000,
    0b11100000,
    0b11111111,
    0b11111111,
    0b00000000,
    0b00000000,

    0b00000000,
    0b00000000,
    0b01111100,
    0b11111110,
    0b11000111,
    0b00000011,
    0b00000111,
    0b00011110,
    0b00011110,
    0b00000111,
    0b00000011,
    0b11000111,
    0b11111110,
    0b01111100,
    0b00000000,
    0b00000000,

    0b00000000,
    0b00000000,

    0b00001110,
    0b00011110,
    0b00111110,
    0b01110110,
    0b11100110,
    0b11000110,
    0b11000110,
    0b11111111,
    0b11111111,
    0b00000110,
    0b00000110,
    0b00000110,
    0b00000000,
    0b00000000,


    0b00000000,
    0b00000000,
    0b11111111,
    0b11111111,
    0b11000000,
    0b11011100,
    0b11111110,
    0b11110111,
    0b11100011,
    0b00000011,
    0b00000011,
    0b11000111,
    0b11111110,
    0b01111100,
    0b00000000,
    0b00000000,


    0b00000000,
    0b00000000,
    0b00111100,
    0b01111110,
    0b11100110,
    0b11000000,
    0b11011100,
    0b11111110,
    0b11110111,
    0b11000011,
    0b11000011,
    0b11100111,
    0b01111110,
    0b00111100,
    0b00000000,
    0b00000000,

    0b00000000,
    0b00000000,
    0b11111111,
    0b11111111,
    0b00000011,
    0b00000111,
    0b00000110,
    0b00001110,
    0b00001100,
    0b00011100,
    0b00011000,
    0b00111000,
    0b00110000,
    0b01110000,
    0b00000000,
    0b00000000,

    0b00000000,
    0b00000000,
    0b00111100,
    0b01111110,
    0b11100111,
    0b11000011,
    0b11100111,
    0b01111110,
    0b01111110,
    0b11100111,
    0b11000011,
    0b11100111,
    0b01111110,
    0b00111100,
    0b00000000,
    0b00000000,

    0b00000000,
    0b00000000,
    0b00111100,
    0b01111110,
    0b11100111,
    0b11000011,
    0b11000011,
    0b11101111,
    0b01111111,
    0b00111011,
    0b00000011,
    0b01100111,
    0b01111110,
    0b00111100,
    0b00000000,
    0b00000000,

  };
  
  int photo_resistor = analogRead(A0);
  PRINTS("ANALOG: ");
  PRINTD(photo_resistor);

  if (photo_resistor>700) {
    mx.control(MD_MAX72XX::SHUTDOWN, MD_MAX72XX::OFF);
    // mx.control(MD_MAX72XX::INTENSITY, 0);

    bool flag24 = false;
    bool pmFlag = false;
    uint8_t hour = myRTC.getHour(flag24, pmFlag);
    uint8_t min = myRTC.getMinute();

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    dht.begin();
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();

    if (!(isnan(h) || isnan(t))) {
      PRINTS("HUM:");
      PRINTD((int)h);
      PRINTS("TEMP:");
      PRINTD((int)(t * 10));
    } else {
      PRINTS("Failed to read temp\n");
    }

    mx.clear();

    mx.setBuffer(9 * COL_SIZE - 1, COL_SIZE, zero + COL_SIZE * (2 * (hour / 10) + 1));
    mx.setBuffer(1 * COL_SIZE - 1, COL_SIZE, zero + COL_SIZE * (2 * (hour / 10)));

    mx.setBuffer(10 * COL_SIZE - 1, COL_SIZE, zero + COL_SIZE * (2 * (hour % 10) + 1));
    mx.setBuffer(2 * COL_SIZE - 1, COL_SIZE, zero + COL_SIZE * (2 * (hour % 10)));

    mx.setBuffer(11 * COL_SIZE - 1, COL_SIZE, zero + COL_SIZE * (2 * (min / 10) + 1));
    mx.setBuffer(3 * COL_SIZE - 1, COL_SIZE, zero + COL_SIZE * (2 * (min / 10)));

    mx.setBuffer(12 * COL_SIZE - 1, COL_SIZE, zero + COL_SIZE * (2 * (min % 10) + 1));
    mx.setBuffer(4 * COL_SIZE - 1, COL_SIZE, zero + COL_SIZE * (2 * (min % 10)));
    mx.transform(MD_MAX72XX::TRC);



    if (!(isnan(h) || isnan(t))) {
      mx.setChar((6 * COL_SIZE) - 1, '0' + ((int)h) / 10);
      mx.setChar((7 * COL_SIZE) - 1, '0' + ((int)h) % 10);
      mx.setChar((8 * COL_SIZE) - 1, '%');

      mx.setChar((14 * COL_SIZE) - 1, '0' + ((int)t) / 10);
      mx.setChar((15 * COL_SIZE) - 1, '0' + ((int)t) % 10);
      mx.setChar((16 * COL_SIZE) - 1, '0' + ((int)(t * 10)) % 10);

      mx.setPoint(6, (15 * COL_SIZE) - 7, true);

      mx.setPoint(0, (16 * COL_SIZE) - 8, true);
      mx.setPoint(1, (16 * COL_SIZE) - 8, true);
      mx.setPoint(0, (16 * COL_SIZE) - 7, true);
      mx.setPoint(1, (16 * COL_SIZE) - 7, true);
    }

  }  else {
    mx.control(MD_MAX72XX::SHUTDOWN, MD_MAX72XX::ON);
  }
   delay(10);

  mx.update();
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  // mx.control(MD_MAX72XX::SHUTDOWN, true);

  // LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  // mx.begin();
}

void loop() {
  display_time_example2();
}
