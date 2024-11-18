#ifndef WEB_HPP
#define WEB_H
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include "network.hpp"

class Web {
public:
    // Konstruktor z portem (domyślnie 80)
    Web(uint16_t port = 80) : server(port) {}

    void setup();
    void saveNetwork(AsyncWebServerRequest *request);
    void updateHandler(AsyncWebServerRequest *request, const String &filename, size_t index, uint8_t *data, size_t len, bool final);
    size_t updateContentLen;

private:
    AsyncWebServer server;
};

extern Web web;

#endif
