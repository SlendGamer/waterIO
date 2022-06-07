#pragma once

#include <Arduino.h>
#include <stdint.h>

#define __AVR_ATmega328P__

// GPIO defines
#define RELAY_1 1
#define RELAY_2 2
#define RELAY_3 3
#define RELAY_4 4

#define VALVE_1 RELAY_1
#define VALVE_2 RELAY_2
#define VALVE_3 RELAY_3
#define VALVE_4 RELAY_4

#define HUM_SENSOR_1 5
#define HUM_SENSOR_2 4
#define HUM_SENSOR_3 5
#define HUM_SENSOR_4 5

#define ZONE_1 1
#define ZONE_2 2
#define ZONE_3 3
#define ZONE_4 4

// waterIO class
class WaterIO {
public:
    waterIO();
    static WaterIO& instance() {
        static WaterIO instance;
        return instance;
    }

// boot section
void setup();
void loop();
void reset();

// additional functions
};

class Valve {
public:
    uint8_t valveNum;
    uint8_t valvePin;
    Zone** zoneChildren;

void init();
};

class Zone {
public:
    uint8_t zoneNum;
    uint8_t zonePin;
    Sensor** sensorChildren;
    Valve* valveParent;

void init();
};

class Sensor {
public:
    uint8_t sensorNum;
    uint8_t sensorPin;
    Zone* zoneParent;

void init();
};