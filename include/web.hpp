#ifndef WEB_HPP
#define WEB_HPP

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <Update.h>
#include "network.hpp"
#include "dhtData.hpp"
#include "SDcard.hpp"

class Web {
public:
    // Konstruktor z portem (domyślnie 80)
    Web(): server(80), updateContentLen(0) {}

    void setup();
    void saveNetwork(AsyncWebServerRequest *request);
    void getData(AsyncWebServerRequest *request);
    bool loadStaticFiles();

private:
    AsyncWebServer server;
    size_t updateContentLen;

};

extern Web web;
#endif
