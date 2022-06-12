#pragma once

#include <Arduino.h>
#include <stdint.h>

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

/*
 Any identification numbers of objects shall only change during boot or when 
 changing the settings
*/

class WaterIO;
class OnOffDevice;
class Sensor;
class Zone;
class Valve;
class Pump;
class Reservoir;

template<typename T>
uint16_t arrayLength(T**);

// waterIO class
class WaterIO {
public:
    // WaterIO();
    // static WaterIO& instance() {
    //     static WaterIO instance;
    //     return instance;
    // }

    Reservoir** reservoir;
    Pump** pumps;
    Valve** valves;
    Zone** zones;
    Sensor** sensors;

// boot section
void setup();
void loop();
void reset();
}waterIO;

enum deviceFlags: uint8_t {
    IS_ACTIVE = (uint8_t) (1 << 0),
    RESERVED = (uint8_t) (1 << 1),
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

class Reservoir {
public:
    Pump** pumps;
    uint8_t sensorPin;
    uint8_t isEmpty;
};

// pumps
class Pump: public OnOffDevice {
public:
    Reservoir* reservoir;
    Valve** valves;
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
// optimally, a zone should only represent one plant, pot or basket 
class Zone {
public:
    Valve* valve;       // parent valve node
    Sensor** sensors;   // children sensor nodes
    uint8_t id;         // unique identification number

    uint32_t checkInterval; // in milliseconds
    float waterOnTime;
    uint8_t threshold;

void init();
uint8_t getHumidity();
void startWater();
void stopWater();
};

// sensors for measuring humidity in one or multiple zones
class Sensor {
public:
    Zone* zone;     // zone dependency
    uint8_t id;     // unique identification number
    uint8_t pin;    // hardware pin

    float calibrationConstant;

void init();
uint8_t getHumidity();
void calibration();
};