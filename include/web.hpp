#ifndef WEB_HPP
#define WEB_H
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <Update.h>
#include "network.hpp"
#include "dhtData.hpp"

class Web {
public:
    // Konstruktor z portem (domyślnie 80)
    Web(): server(80), updateContentLen(0) {}

    void setup();
    void saveNetwork(AsyncWebServerRequest *request);
    void logToSocket(int level, const String &message1, const String &message2, String value, const tm &timeinfo);
    void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
    void updateHandler(AsyncWebServerRequest *request, const String &filename, size_t index, uint8_t *data, size_t len, bool final);
    String template_proc(const String &var);
    void getData(AsyncWebServerRequest *request);

private:
    AsyncWebServer server;
    size_t updateContentLen;

};

extern Web web;

#endif
