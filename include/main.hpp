#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include "web.hpp"
#include "SDcard.hpp"

// Deklaracja funkcji inicjalizujących
void setup();
void loop();

// Funkcje pomocnicze
void initFilesystem();
void initWiFi();
void hardwareInit();
void getData();


extern Web web; // Deklaracja obiektu Web
extern Network network; // Deklaracja obiektu Network
extern Sd_card sdCard;
#endif // MAIN_H
