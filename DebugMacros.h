#pragma once

#define DEBUG 0

#if DEBUG
#define DEBUG_PRINT(s, x) \
  { \
    Serial.print(F(s)); \
    Serial.print(x); \
  }
#define DEBUG_PRINTS(x) Serial.print(F(x))
#define DEBUG_PRINTD(x) Serial.println(x, DEC)
#define DEBUG_INITIALIZE() \
  { \
    Serial.begin(57600); \
    while(!Serial) {;} \
  }
#define DEBUG_FLUSH() Serial.flush()

#else

#define DEBUG_PRINT(s, x)
#define DEBUG_PRINTS(x)
#define DEBUG_PRINTD(x)
#define DEBUG_FLUSH()
#define DEBUG_INITIALIZE()

#endif