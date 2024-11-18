#ifndef NETWORKPREFERENCES_HPP
#define NETWORKPREFERENCES_HPP

#include <Preferences.h>
#include <Arduino.h>

#define ESSID "GREENHOUSE"
#define PW "GREENHOUSE"

class preferencesHandler {
public:
  Preferences preferences;
  
  String ssid;
  String pw;
  String wifiMode;

  // Metody do zapisywania i odczytywania ustawień
  void saveNetworkValues();
  void saveSettings();
  void readNetworkValues();
  void readSettings();
  void preferencesClear();
};

extern preferencesHandler handlePreferences;

#endif // NETWORKPREFERENCES_HPP
