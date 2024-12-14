#include "DataJson.hpp"

DataHandler dataHandler;

bool DataHandler::createDataJson() {
    // Sprawdź, czy plik już istnieje
    if (SD_MMC.exists(dataFilePath)) {
        Serial.println("[INFO] Plik już istnieje.");
        return true; // Plik już istnieje
    }

    // Utwórz nowy plik
    File file = SD_MMC.open(dataFilePath, FILE_WRITE);
    if (!file) {
        Serial.println("[ERROR] Nie można otworzyć pliku do zapisu.");
        return false;
    }
    file.close();
    Serial.println("[INFO] Plik data.json utworzony.");
    return true;
}

String DataHandler::updateJsonDoc(SensorData data) {
    doc["temperature"] = data.temperature;
    doc["humidity"] = data.humidity;
    doc["soil_humidity"] = data.soil_humidity;
    doc["CO2"] = data.co2;
    doc["timestamp"] = data.timestamp;
    String jsonDoc;
    serializeJson(doc,jsonDoc);
    return jsonDoc;
}

bool DataHandler::saveJsonToSDcard() {
    // Sprawdzenie, czy karta SD została poprawnie zainicjalizowana
      fs::FS &fs = SD_MMC; 

    File file = fs.open(dataFilePath, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file in writing mode");
        return false;
    }
    
    // Zserializuj dokument JSON do pliku
    if (serializeJson(doc, file) == 0) {
        Serial.println("Błąd podczas serializacji JSON.");
        file.close();  // Zamknij plik, jeśli wystąpił błąd
        return false;
    }

    // Dodaj nową linię po zapisaniu JSON, aby oddzielić wpisy
    file.println();
    file.close();  // Zamknij plik po zapisaniu
    Serial.println("JSON zapisany na karcie SD.");
    return true;
}