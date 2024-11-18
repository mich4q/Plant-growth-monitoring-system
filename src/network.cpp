#include <Arduino.h>
#include "network.hpp"

void Network::init(){
    setWifiMode();
}

void Network::setWifiMode(){
    const char* ssid = handlePreferences.ssid.c_str();
    const char* password = handlePreferences.pw.c_str();
    const char* wifiMode = handlePreferences.wifiMode.c_str();
    if (strcmp(wifiMode, "AP") == 0) {
      Serial.println("Setting WiFi in AP mode: ");
      Serial.printf("*%s*\n", wifiMode);
      WiFi.mode(WIFI_OFF);
      WiFi.mode(WIFI_AP);
      WiFi.softAP(ssid, password);
      if (!MDNS.begin(hostname)) { 
        Serial.println("Error setting up MDNS  responder");
      } else {
        Serial.println("mDNS responder started");
      }
    } else {
      Serial.println("Setting WiFi in Client mode");
      Serial.printf("*%s*\n", wifiMode);
      WiFi.mode(WIFI_OFF);
      WiFi.mode(WIFI_STA);
      WiFi.setHostname(hostname);
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print("Connecting to WiFi: ");
        Serial.println(ssid);
        Serial.println(password);
      }
      Serial.println("Connected to the WiFi network");
      Serial.print("IP address: ");
      IPAddress ip = WiFi.localIP();
      Serial.println(ip);

      if (!MDNS.begin(hostname)) {
        Serial.println("Error setting up MDNS  responder");
      } else {
        Serial.println("mDNS responder started");
      }
    }
}

