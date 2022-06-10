#pragma once

#include <Arduino.h>
#include <stdint.h>

#define __AVR_ATmega328P__

#ifdef __AVR_ATmega328P__
    #define AREF 5
#endif
#ifdef ESP32
    #define AREF 3.33f
#endif

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

#define HIGH_ACTIVE 0x01
#define LOW_ACTIVE  0x00

#define SET_BIT(x, y)   (y |= x)
#define RESET_BIT(x, y) (y &= ~x)

// waterIO class
class WaterIO {
public:
    WaterIO();
    static WaterIO& instance() {
        static WaterIO instance;
        return instance;
    }

    Pump** pumps;
    Valve** valves;
    Zone** zones;
    Sensor** sensors;

// boot section
void setup();
void loop();
void reset();
}waterIO;

/*
 Any identification numbers of objects shall only change during boot or when 
 changing the settings
*/

enum deviceFlags: uint8_t {
    IS_ACTIVE = (uint8_t) (1 << 0),
    RESERVED = (uint8_t) (1 << 1),
    RESERVED = (uint8_t) (1 << 2),
    RESERVED = (uint8_t) (1 << 3),
    RESERVED = (uint8_t) (1 << 4),
    RESERVED = (uint8_t) (1 << 5),
    RESERVED = (uint8_t) (1 << 6),
    BYPASS_VALVE = (uint8_t) (1 << 7)
};

class OnOffDevice {
public:
    uint8_t id; // device id
    uint8_t pin; // device gpio pin
    uint8_t flags;
    uint8_t activeLevel;

void init();
void activate();
void deactivate();
};

// pumps
class Pump: public OnOffDevice {
public:
    Valve** valves;
    Zone** zones; // in case a pump is connected directly to one ore multiple zones
    float flow;

};

// valves
class Valve: public OnOffDevice {
public:
    Pump* pump;
    Zone** zones;

};

// zones have no hardware
// a zone is an area where water should be applied
// optimally, a zone should only represent one plant pot or basket 
class Zone {
public:
    Valve* valve;   // parent valve node
    Sensor** sensors; // children sensor nodes
    uint8_t id; //

    uint16_t checkInterval;
    uint8_t threshold;
    uint8_t humidity;

void init();
void getHumidity();
};

// sensors for measuring humidity in one or multiple zones
class Sensor {
public:
    Zone* zone; // zone dependency
    uint8_t id; // unique identification number
    uint8_t pin; // hardware pin

    uint8_t humidity;
    float calibrationConstant;

void init();
void getHumidity();
void calibration();
};