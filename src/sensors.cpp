#include "sensors.hpp"

Sensors sensors;

DHT dht22(DHT_PIN, DHT_TYPE);

void Sensors::init(){
    dhtInit();
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void Sensors::dhtInit(){
    dht22.begin();
}
SensorData Sensors::getData(){
    SensorData data;
    data.temperature = dht22.readTemperature();
    data.humidity = dht22.readHumidity();
    data.co2 = 0;
    data.soil_humidity = 0;
    data.timestamp = getTimestamp();

    return data;
}

String Sensors::getTimestamp(){
        
    struct tm timeinfo;
    // Pobranie lokalnego czasu
    if (!getLocalTime(&timeinfo)) {
        return "Brak synchronizacji czasu"; // Obsługa błędu
    }

    // Konwersja czasu do formatu "YYYY-MM-DD HH:MM:SS"
    char timeStampBuffer[20];
    strftime(timeStampBuffer, sizeof(timeStampBuffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
    
    return String(timeStampBuffer); // Zwrócenie jako String
}