#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include "web.hpp"
#include "SDcard.hpp"
#include "soc/soc.h"           // Disable brownout problems
#include "soc/rtc_cntl_reg.h"  // Disable brownout problems
// Deklaracja funkcji inicjalizujących
void setup();
void loop();

// Funkcje pomocnicze
void initFilesystem();
void initWiFi();
void hardwareInit();


extern Web web; // Deklaracja obiektu Web
extern Network network; // Deklaracja obiektu Network
extern Sd_card sdCard;
#endif // MAIN_H
