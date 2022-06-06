#pragma once

// library includes

#define DEBUG

#define ATmega32

// GPIO defines
#define REL1 1
#define REL2 2

#define SENS_HUM1 3
#define SENS_HUM2 4
#define SENS_HUM3 5

// waterIO class
class waterIO {
public:
    waterIO();
    static waterIO& instance() {
        static waterIO instance;
        return instance;
    }

// boot section
void setup();
void loop();
void reset();

// additional functions


};