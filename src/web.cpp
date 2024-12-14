#include "web.hpp"
#include "DataJson.hpp"
Web web; 

#include <Arduino.h>
#include "web.hpp"
#include "LittleFS.h"

void Web::setup() {
    // Wczytywanie plików przed uruchomieniem serwera
    if (loadStaticFiles()) {
        // Obsługa głównej strony, wysyłanie pliku index.html
        server.on("/", HTTP_ANY, [this](AsyncWebServerRequest *request) {
            request->send(LittleFS, "/index.html", "text/html");
        });

        // Obsługa zapisu ustawień sieciowych
        server.on("/savenetwork", HTTP_GET, [this](AsyncWebServerRequest *request) { 
            saveNetwork(request); 
        });

        server.on("/getData", HTTP_GET, [this](AsyncWebServerRequest *request) {
            getData(request);
        });

        // Obsługa nieznanych zapytań (404)
        server.onNotFound([](AsyncWebServerRequest *request) { 
            request->send(404); 
        });

        // Obsługa statycznych plików (JavaScript, CSS, obrazy)
        server.serveStatic("/js/", LittleFS, "/js/");
        server.serveStatic("/css/", LittleFS, "/css/");
        
        // Rozpoczęcie działania serwera
        server.begin();
        Serial.println("Serwer uruchomiony.");
    } else {
        Serial.println("Błąd ładowania plików statycznych.");
    }
}

bool Web::loadStaticFiles() {
    // Sprawdzanie, czy wszystkie wymagane pliki istnieją w systemie plików
    if (!LittleFS.exists("/index.html") || !LittleFS.exists("/js/main.js") || !LittleFS.exists("/css/main.css")) {
        Serial.println("Brak wymaganych plików w systemie plików.");
        return false;  // Pliki nie istnieją, zwróć false
    }

    // Próba otwarcia plików (wczytywanie danych)
    File indexFile = LittleFS.open("/index.html", "r");
    if (!indexFile) {
        Serial.println("Nie udało się otworzyć pliku index.html.");
        return false;
    }
    indexFile.close();

    File jsFile = LittleFS.open("/js/main.js", "r");
    if (!jsFile) {
        Serial.println("Nie udało się otworzyć pliku main.js.");
        return false;
    }
    jsFile.close();

    File cssFile = LittleFS.open("/css/main.css", "r");
    if (!cssFile) {
        Serial.println("Nie udało się otworzyć pliku main.css.");
        return false;
    }
    cssFile.close();

    // Jeśli wszystkie pliki zostały pomyślnie otwarte, zwróć true
    return true;
}

void Web::getData(AsyncWebServerRequest *request){
    String jsonResponse;
    serializeJson(dataHandler.doc,jsonResponse);
    Serial.println(jsonResponse);
    request->send(200, "application/json", jsonResponse); // Wysyła odpowiedź jako JSON
}

void Web::saveNetwork(AsyncWebServerRequest *request) {
    // Sprawdzenie, czy wszystkie wymagane parametry są dostępne
    if (request->hasParam("ssid") && request->hasParam("password") && request->hasParam("wifiMode")) {
        String ssid = request->getParam("ssid")->value();  // Pobranie wartości SSID
        String password = request->getParam("password")->value();  // Pobranie wartości hasła
        String wifiMode = request->getParam("wifiMode")->value();  // Pobranie wartości trybu Wi-Fi

        // Upewnienie się, że wartości nie są puste
        if (!ssid.isEmpty() && !password.isEmpty() && !wifiMode.isEmpty()) {
            // Zapisanie wartości do obiektu handlePreferences
            handlePreferences.ssid = ssid;
            handlePreferences.pw = password;
            handlePreferences.wifiMode = wifiMode;
            // Zapisanie ustawień w pamięci
            handlePreferences.saveNetworkValues();

            network.setWifiMode();  // Zmiana trybu Wi-Fi
            Serial.println(handlePreferences.ssid);
            Serial.println(handlePreferences.pw);
            Serial.println(handlePreferences.wifiMode);

            // Wysłanie odpowiedzi HTTP 200, że dane zostały zapisane
            request->send(200, "text/plain", "Network settings updated");
        } else {
            // W przypadku pustych parametrów
            request->send(400, "text/plain", "Invalid or empty parameters");
        }
    } else {
        // W przypadku braku któregokolwiek z parametrów
        request->send(400, "text/plain", "Missing parameters");
    }
}