#ifndef MQTT_H
#define MQTT_H

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>


const char* ssid = "A54";
const char* password = "onow5432";

const char* mqttServer = "192.168.1.100"; // Da sistemare inserire indirizzo del broker

const int mqttPort = 8883;
const char* mqttUser = "admin";
const char* mqttPassword = "public";

const char* ca_cert = R"EOF(
    -----BEGIN CERTIFICATE-----
    MIID... (taglia il certificato PEM qui)
    -----END CERTIFICATE-----
    )EOF";


class Omqx {
private:
    WiFiClient espClient;
    PubSubClient client(espClient); 

public:
    Omqx() {

        espClient.setCACert(ca_cert); 

        setup_wifi();
        client.setServer(mqttServer, mqttPort);
        client.setCallback(callback);
    }

    void setup_wifi() {
        delay(10);
        Serial.println();
        Serial.print("Connessione a WiFi...");
        WiFi.begin(ssid, password);

        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }

        Serial.println("\nWiFi connesso");
        Serial.print("Indirizzo IP: ");
        Serial.println(WiFi.localIP());
    }

    static void callback(char* topic, byte* payload, unsigned int length) {
        Serial.print("Messaggio ricevuto su topic: ");
        Serial.println(topic);

        char jsonBuffer[length + 1];
        memcpy(jsonBuffer, payload, length);
        jsonBuffer[length] = '\0';

        StaticJsonDocument<256> doc;
        DeserializationError error = deserializeJson(doc, jsonBuffer);

        if (error) {
            Serial.print("Errore parsing JSON: ");
            Serial.println(error.c_str());
            return;
        }

        int speed = doc["speed"];
        int duration = doc["duration"];
        const char* direction = doc["direction"];

        Serial.println("==== Comando Ricevuto ====");
        Serial.print("Speed: "); Serial.println(speed);
        Serial.print("Duration: "); Serial.println(duration);
        Serial.print("Direction: "); Serial.println(direction);
        Serial.println("==========================");
    }

    void reconnect() {
        while (!client.connected()) {
            Serial.print("Connessione al broker MQTT...");
            String clientId = "ESP32Client-" + String(WiFi.macAddress());  
            if (client.connect(clientId.c_str(), mqttUser, mqttPassword)) {
                Serial.println("Connesso!");
                client.subscribe("arduino/camera");
            } else {
                Serial.print("Errore, rc=");
                Serial.print(client.state());
                Serial.println("... riprovo in 5 secondi");
                delay(5000);
            }
        }
    }

    void loop() {
        if (!client.connected()) {
            reconnect();
        }
        client.loop();
    }
};

#endif