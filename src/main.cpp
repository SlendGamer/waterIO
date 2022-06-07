#include "main.h"

void setup() {
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, OUTPUT);

  pinMode(HUM_SENSOR_1, INPUT);
  pinMode(HUM_SENSOR_2, INPUT);
  pinMode(HUM_SENSOR_3, INPUT);
  pinMode(HUM_SENSOR_4, INPUT);

  Valve valve1;
  valve1.valveNum = 0;
  valve1.valvePin = 1;
  valve1.init();
  
  Zone zone1;
  zone1.zoneNum = 0;

  Sensor sensor1;
  sensor1.sensorNum = 0;
  sensor1.init();


}

void loop() {
  uint8_t currentZoneHumidity;

  for(uint8_t i = ZONE_1; i <= ZONE_4; i++) {
    currentZoneHumidity = checkZone(i);

  }



}


// humidity values: 
// 254 => 100%
// 001 => 0%
// 000 => error
uint8_t checkZone(uint8_t zone) {
  uint8_t zoneHumidity = 0;
  analogRead()
  return zoneHumidity;
}

void Valve::init() {
  pinMode(valvePin, OUTPUT);
}

void Sensor::init() {
  pinMode(sensorPin, INPUT);
}