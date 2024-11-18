#include "networkPreferences.hpp"

void preferencesHandler::saveNetworkValues() {
  if (preferences.begin("network", false)) {
    preferences.putString("ssid", ssid);
    preferences.putString("pw", pw);
    preferences.putString("wifiMode", wifiMode);
    Serial.println("Network preferences updated");
    preferences.end();
  } else {
    Serial.println(F("writing network preferences failed"));
  }
}

void preferencesHandler::readNetworkValues() {
  if (preferences.begin("network", false)) {
    ssid = preferences.getString("ssid", ESSID);
    pw = preferences.getString("pw", PW);
    wifiMode = preferences.getString("wifiMode", "AP");
    Serial.printf(
        "Values from network preferences: \n ssid:%s, pw:%s, mode:%s\n ",
        ssid.c_str(), pw.c_str(), wifiMode.c_str());
  } else {
    Serial.println(F("reading preferences failed"));
  }
  preferences.end();
}

void preferencesHandler::preferencesClear() { 
  preferences.clear(); 
}
preferencesHandler handlePreferences;
