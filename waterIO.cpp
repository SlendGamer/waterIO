#include "waterIO.h"
#include "stdint.h"

int8_t check_rain = false;

void waterIO::setup() {   
while (1) {

#if defined(ATmega32)

// check soil humidity



// check for rain (maybe with an interrupt)
if(check_rain) {

}

// enable relays


#endif

#ifdef ESP32

#endif

} 
return 0;
}
