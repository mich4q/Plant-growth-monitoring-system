#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include "web.hpp"


// Deklaracja funkcji inicjalizujących
void setup();
void loop();

// Funkcje pomocnicze
void initFilesystem();
void initWiFi();
void hardwareInit();

extern Web web; // Deklaracja obiektu Web
extern Network network; // Deklaracja obiektu Network

#endif // MAIN_H
