#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include "web.hpp"
#include "SDcard.hpp"
#include "sensors.hpp"


// Deklaracja funkcji inicjalizujących
void setup();
void loop();

// Funkcje pomocnicze
void initFilesystem();
void initWiFi();
void hardwareInit();

#endif // MAIN_H
