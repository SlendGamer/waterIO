#include "main.h"

void setup() {
  
  Reservoir reservoir1;

  Pump pump1;
  pump1.pin = 6;
  pump1.activeLevel = HIGH_ACTIVE;

  Valve valve1, valve2;
  valve1.pin = 5;
  valve1.activeLevel = HIGH_ACTIVE;
  valve2.pin = 4;
  valve2.activeLevel = HIGH_ACTIVE;

  Zone zone1, zone2;
  zone1.checkInterval = 10000;
  zone1.threshold = 150;
  zone2.checkInterval = 10000;
  zone2.threshold = 150;

  Sensor sensor1, sensor2;
  sensor1.pin = 7;
  sensor1.calibrationConstant = 1;
  sensor2.pin = 6;
  sensor1.calibrationConstant = 1;

// pointer references
// children
  waterIO.reservoir = new Reservoir*[1] {&reservoir1};
  waterIO.pumps = new Pump*[1] {&pump1};
  waterIO.valves = new Valve*[2] {&valve1, &valve2};
  waterIO.zones = new Zone*[2] {&zone1, &zone2};
  waterIO.sensors = new Sensor*[2] {&sensor1, &sensor2};

  reservoir1.pumps = new Pump*[1] {&pump1};

  pump1.valves = new Valve*[2] {&valve1, &valve2};

  valve1.zones = new Zone*[1] {&zone1};
  valve2.zones = new Zone*[1] {&zone2};

  zone1.sensors = new Sensor*[1] {&sensor1};
  zone2.sensors = new Sensor*[1] {&sensor2};

// parents
  pump1.reservoir = &reservoir1;

  valve1.pump = &pump1;
  valve2.pump = &pump1;

  zone1.valve = &valve1;
  zone2.valve = &valve2;

  sensor1.zone = &zone1;
  sensor2.zone = &zone2;

// initilization
  for(uint8_t i = 1; i < arrayLength(waterIO.pumps); i++) {
    waterIO.pumps[i - 1]->init();
  }

  for(uint8_t i = 1; i < arrayLength(waterIO.valves); i++) {
    waterIO.valves[i - 1]->init();
  }

  Serial.begin(9600);

  Serial.println("Booting...");

}

unsigned long lastMillis = 0;
void loop() {

  if(millis() - lastMillis > 10000) {
    Serial.println("Test");
    uint16_t zoneCount = arrayLength(waterIO.zones);
    Zone* tempZone;

    for (uint8_t i = 0; i < zoneCount; i++) {
      tempZone = waterIO.zones[i];

      // DEBUG
      Serial.print("Zone ");
      Serial.print(i);
      Serial.print(": ");
      Serial.print(tempZone->getHumidity());

      if(tempZone->getHumidity() < tempZone->threshold) {

        tempZone->startWater();
        delay(tempZone->waterOnTime);
        tempZone->stopWater();
      }
    }
  
    lastMillis = millis();
  }

}

// custom function to return array length
// of a pointer array of any type
template<typename T>
uint16_t arrayLength(T** arrayPtr) { return sizeof(*arrayPtr)/sizeof(**arrayPtr); }

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

uint8_t Zone::getHumidity() {
  uint16_t sensorCount = arrayLength(sensors);
  uint8_t temp = 0;

  // with one sensor per zone, the sensor value can just be copied
  if (sensorCount == 1) { temp = sensors[0]->getHumidity(); }

  // multiple sensor values have to be averaged 
  else if (sensorCount > 1) {
    for (uint8_t i = 0; i < sensorCount; i++) {
      temp += sensors[i]->getHumidity();
    }
    temp = temp / sensorCount;
  }

  return temp;
}

void Zone::startWater() {
  valve->activate();
  valve->pump->activate();
}

void Zone::stopWater() {
  valve->deactivate();
  valve->pump->deactivate();
}

// initializes sensor instance
void Sensor::init() {
  pinMode(pin, INPUT);
}

/*  linear approximation of humidity curve
  humidity values 
  255 => 100%
  000 => 0% */
uint8_t Sensor::getHumidity() { return (analogRead(pin) * calibrationConstant); }

void Sensor::calibration() {
  // sensor in dry air (0%)
  uint8_t dry = (analogRead(pin) / 1024);
  
  // wait for user input
  delay(5000);

  // sensor submerged in water (100%)
  uint8_t wet = (analogRead(pin) / 1024);

  if(dry == wet){} // error

  // linear approximation of humidity curve
  calibrationConstant = 255 / (wet - dry);
}
