#pragma once
#include <DS3231.h>

class RTime {
public:
  inline uint8_t getHour() { return hour; }
  inline uint8_t getMinute() { return minute; }
  inline RTime(uint8_t hour, uint8_t minute) {
    this->hour = hour;
    this->minute = minute;
  }
private:
  uint8_t hour;
  uint8_t minute;
};

class RTClock {
public:
  RTime readTime();
private:
  DS3231 rtc = DS3231();  
};
