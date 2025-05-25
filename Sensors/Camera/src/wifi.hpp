#ifndef WIFI_H
#define WIFI_H

#include <WiFi.h>

const char* ssid = "A54";
const char* password = "onow5432";

void connectWifi() {
    delay(10);
    Serial.println("\nConnecting to WiFi...");
    WiFi.begin(ssid, password);

    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connect to ");
    Serial.println(WiFi.localIP());
}

#endif