#include "main.h"

void setup() {

  Pump pump1;
  pump1.pin = 1;
  pump1.activeLevel = HIGH_ACTIVE;

  Valve valve1, valve2;
  valve1.pin = 2;
  valve1.activeLevel = HIGH_ACTIVE;
  valve2.pin = 3;
  valve2.activeLevel = HIGH_ACTIVE;

  Zone zone1, zone2;

  Sensor sensor1, sensor2;

// pointer references
// children
  waterIO.pumps = new Pump*[1] {&pump1};
  waterIO.valves = new Valve*[2] {&valve1, &valve2};
  waterIO.zones = new Zone*[2] {&zone1, &zone2};
  waterIO.sensors = new Sensor*[2] {&sensor1, &sensor2};

  pump1.valves = new Valve*[2] {&valve1, &valve2};

  valve1.zones = new Zone*[1] {&zone1};
  valve2.zones = new Zone*[1] {&zone2};

  zone1.sensors = new Sensor*[1] {&sensor1};
  zone2.sensors = new Sensor*[1] {&sensor2};

// parents
  valve1.pump = &pump1;
  valve2.pump = &pump1;

  zone1.valve = &valve1;
  zone2.valve = &valve2;

  sensor1.zone = &zone1;
  sensor2.zone = &zone2;

// initilization
uint8_t arrayLength = (sizeof(*waterIO.pumps)/sizeof(**waterIO.pumps)) + 1;
for(uint8_t i = 0; i < arrayLength; i++) {
  waterIO.pumps[i];
}


}

void loop() {

}

// initializes valve instance
void OnOffDevice::init() {
  pinMode(pin, OUTPUT);
}

void OnOffDevice::activate() {
  digitalWrite(pin, activeLevel);
  SET_BIT(IS_ACTIVE, flags);
}

void OnOffDevice::deactivate() {
  digitalWrite(pin, !activeLevel);
  RESET_BIT(IS_ACTIVE, flags);
}

// initializes sensor instance
void Sensor::init() {
  pinMode(pin, INPUT);
}

// linear approximation of humidity curve
// humidity values 
// 255 => 100%
// 000 => 0%
void Sensor::getHumidity() {
  humidity = analogRead(pin) * calibrationConstant;
}

void Sensor::calibration() {
  // sensor in dry air (0%)
  uint8_t dry = (analogRead(pin) / 1024);
  
  // wait for user input

  // sensor submerged in water (100%)
  uint8_t wet = (analogRead(pin) / 1024);

  if(dry == wet){} // print error

  // linear approximation of humidity curve
  calibrationConstant = 255 / (wet - dry);
}

void Zone::getHumidity() {
  humidity = 0;

}
