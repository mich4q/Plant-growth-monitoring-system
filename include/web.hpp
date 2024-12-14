#ifndef WEB_HPP
#define WEB_H
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include "network.hpp"

class Web {
public:
    // Konstruktor z portem (domyślnie 80)
    Web(): server(80) {}

    void setup();
    void saveNetwork(AsyncWebServerRequest *request);
    String template_proc(const String &var);

private:
    AsyncWebServer server;
};

extern Web web;

#endif
