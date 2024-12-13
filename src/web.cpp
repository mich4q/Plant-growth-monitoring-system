#include "web.hpp"

DHTData dhtData;

void Web::setup() {
    // Obsługa głównej strony, wysyłanie pliku index.html
    server.on("/", HTTP_ANY, [this](AsyncWebServerRequest *request) {
        request->send(LittleFS, "/index.html", "text/html", false, [this](const String &var) {
            return this->template_proc(var);
        });
    });

    // Obsługa statycznych plików (JavaScript, CSS, obrazy)
    server.serveStatic("/js/", LittleFS, "/js/");
    server.serveStatic("/css/", LittleFS, "/css/");
    
    // Obsługa zapisu ustawień sieciowych
    server.on("/savenetwork", HTTP_GET, [this](AsyncWebServerRequest *request) { 
        saveNetwork(request); 
    });

    // Obsługa aktualizacji
    server.on("/update", HTTP_POST, [](AsyncWebServerRequest *request) {},
            [this](AsyncWebServerRequest *request, const String &filename, size_t index, uint8_t *data, size_t len, bool final) {
            updateHandler(request, filename, index, data, len, final);
        });
    server.on("/getData", HTTP_GET,[this](AsyncWebServerRequest *request){
        getData(request);
    });
    // Obsługa nieznanych zapytań (404)
    server.onNotFound([](AsyncWebServerRequest *request) { 
        request->send(404); 
    });

    // Rozpoczęcie działania serwera
    server.begin();
}
void Web::getData(AsyncWebServerRequest *request){
    String jsonResponse;
    jsonResponse = dhtData.getDHTData();
    // Serial.println(jsonResponse);
    request->send(200, "application/json", jsonResponse);
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



String Web::template_proc(const String &var) {
    if (var == "FREESPACE") {
        return String(((LittleFS.totalBytes() - LittleFS.usedBytes()) / 1000));
    } else if (var == "USEDSPACE") {
        return String(LittleFS.usedBytes() / 1000);
    } else if (var == "TOTALSPACE") {
        return String(LittleFS.totalBytes() / 1000);
    } else {
        return String("unknown");
    }
}

void Web::updateHandler(AsyncWebServerRequest *request, const String &filename,
                   size_t index, uint8_t *data, size_t len, bool final) {
    if (!index) {
        updateContentLen = request->contentLength();
        int cmd = U_FLASH;
        if (filename == "littlefs.bin") {
            cmd = (filename.indexOf("littlefs") > -1) ? U_SPIFFS : U_FLASH;
        }
        if (!Update.begin(UPDATE_SIZE_UNKNOWN, cmd)) {
            Update.printError(Serial);
        }
    }

    if (Update.write(data, len) != len) {
        Update.printError(Serial);
    }

    if (final) {
        if (!Update.end(true)) {
            updateContentLen = 0;
            Update.printError(Serial);

            char *html = (char *)"<html><head><meta http-equiv='refresh' content='5; url=/update'><title>Update Failed</title></head></html>";
            request->send(200, "text/html", html);
        } else {
            char *html = (char *)"<html><head><meta http-equiv='refresh' content='10; url=/'><title>Rebooting</title></head><body>Rebooting...</body></html>";
            request->send(200, "text/html", html);
            delay(3000);
            ESP.restart();
        }
    }
}

// void Web::logToSocket(int level, const String &message1, const String &message2, String value, const tm &timeinfo) {
//     char timeString[64];
//     strftime(timeString, sizeof(timeString), "%A, %B %d %Y %H:%M:%S", &timeinfo);
    
//     String logMessage = "[" + String(timeString) + "]: " + message1;
    
//     if (message2 != "") {
//         logMessage = logMessage + ": " + message2;
//     }
//     if (value != "nan") {
//         logMessage = logMessage + ": " + value;
//     }
//     if (wsClient != nullptr && wsClient->canSend()) {
//         wsClient->text(logMessage);
//     }
// }

// void Web::onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
//                AwsEventType type, void *arg, uint8_t *data, size_t len) {
//     if (type == WS_EVT_CONNECT) {
//         wsClient = client;
//     } else if (type == WS_EVT_DISCONNECT) {
//         wsClient = nullptr;
//     }
// }