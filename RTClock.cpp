#include "RTClock.h"

RTime RTClock::readTime(){
    bool flag24 = false;
    bool pmFlag = false;
    uint8_t hour = rtc.getHour(flag24, pmFlag);
    uint8_t min = rtc.getMinute();
   
    return RTime(hour, min);
}