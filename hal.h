#ifdef TEENSYDUINO
#include <Arduino.h>

#define log_print(...) Serial.printf(__VA_ARGS__)

#else

#define HOST_BUILD (1)
#include <stdio.h>
#include <string.h>

#define log_print(...) printf(__VA_ARGS__)

#endif
