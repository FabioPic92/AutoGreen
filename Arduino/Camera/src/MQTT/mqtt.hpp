#ifndef MQTT_H
#define MQTT_H

#include <WiFiS3.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* ssid = "A54";
const char* password = "onow5432";

// MQTT
const char* mqttServer = "192.168.180.85";
const int mqttPort = 1883;
const char* mqttUser = "admin";
const char* mqttPassword = "public";

// Certificato (se usi MQTT over TLS/SSL)
const char* ca_cert = R"EOF(
-----BEGIN CERTIFICATE-----
MIID... (taglia il certificato PEM qui)
-----END CERTIFICATE-----
)EOF";

String getMacAddress() {
    uint8_t mac[6];
    WiFi.macAddress(mac);  // Legge il MAC nel buffer
    char macStr[18];       // Formattazione MAC in stringa leggibile
    snprintf(macStr, sizeof(macStr),
             "%02X:%02X:%02X:%02X:%02X:%02X",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return String(macStr);
}

class Omqx {
private:
    WiFiClient espClient;
    PubSubClient client;

    int receivedSpeed = 0;
    int receivedDuration = 0;
    String receivedDirection = "";

public:
    Omqx() : client(espClient) 
    {
    }

    void begin() {
        setup_wifi();
        client.setServer(mqttServer, mqttPort);
        client.setCallback(callbackWrapper);
    }


    void setup_wifi() {
        delay(10);
        Serial.println("\nConnessione a WiFi...");
        WiFi.begin(ssid, password);

        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }

        Serial.println("\nWiFi connesso");
        Serial.print("Indirizzo IP: ");
        Serial.println(WiFi.localIP());
    }

    void reconnect() {
        while (!client.connected()) {
            Serial.print("Connessione al broker MQTT...");
            String clientId = "ESP32Client-" + getMacAddress();
            if (client.connect(clientId.c_str(), mqttUser, mqttPassword)) {
                Serial.println("Connesso!");
                subscribe("raspberry/camera");
            } else {
                Serial.print("Errore, rc=");
                Serial.print(client.state());
                Serial.println("... ritento in 5 secondi");
                delay(5000);
            }
        }
    }

    void subscribe(const char* topic) {
        if (client.connected()) {
            client.subscribe(topic);
            Serial.print("Iscritto al topic: ");
            Serial.println(topic);
        }
    }

    void publish(const char* topic, const char* message) {
        if (client.connected()) {
            client.publish(topic, message);
            Serial.print("Pubblicato su ");
            Serial.print(topic);
            Serial.print(": ");
            Serial.println(message);
        }
    }

    void loop() {
        if(!client.connected()) {
            reconnect();
        }
        client.loop();
    }

    int getSpeed() const { return receivedSpeed; }
    int getDuration() const { return receivedDuration; }
    String getDirection() const { return receivedDirection; }

private:
    static void callbackWrapper(char* topic, byte* payload, unsigned int length) {
        instance->handleCallback(topic, payload, length);
    }

    void handleCallback(char* topic, byte* payload, unsigned int length) {
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

        receivedSpeed = doc["speed"] | 0;
        receivedDuration = doc["duration"] | 0;
        receivedDirection = doc["direction"] | "";

        Serial.println("==== Dati Ricevuti ====");
        Serial.print("Speed: "); Serial.println(receivedSpeed);
        Serial.print("Duration: "); Serial.println(receivedDuration);
        Serial.print("Direction: "); Serial.println(receivedDirection);
        Serial.println("=======================");
    }

    static Omqx* instance;

public:
    static void setInstance(Omqx* inst) {
        instance = inst;
    }

};

Omqx* Omqx::instance = nullptr;

#endif