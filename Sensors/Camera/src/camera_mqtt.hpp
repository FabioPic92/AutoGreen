#ifndef MQTT_H
#define MQTT_H

#include <WiFi.h>
#include <PubSubClient.h>

const char* mqttServer = "192.168.180.85";
const int mqttPort = 1883;
const char* mqttUser = "admin";
const char* mqttPassword = "public";

class CameraMQTT {
private:
    WiFiClient espClient;
    PubSubClient client;
    
public:
    CameraMQTT() 
    : client(espClient) 
    {}

    void begin() {
        client.setServer(mqttServer, mqttPort);
        client.setCallback([this](char* topic, byte* payload, unsigned int length) {
            this->onMessage(topic, payload, length);
        });
    }

    void reconnect() {
        while (!client.connected()) {
            Serial.print("Connecting to MQTT...");
            if (client.connect("ESP32Cam", mqttUser, mqttPassword)) {
                Serial.println("connected");
                client.subscribe("camera/request");  
            } else {
                Serial.print(" failed, rc=");
                Serial.println(client.state());
                delay(2000);
            }
        }
    }

    void publish(const uint8_t* data, size_t len, const char* topic = "camera/image") {
        loop(); 
        client.publish(topic, data, len);
    }

    void loop() {
        if(!client.connected()) {
            reconnect();
        }
        client.loop();
    }
private:
    void onMessage(char* topic, byte* payload, unsigned int length) {
        Serial.print("Messaggio ricevuto su topic: ");
        Serial.println(topic);

        if (strcmp(topic, "camera/request") == 0) {
            Serial.println("Scatto della foto richiesto!");

        //     camera_fb_t* fb = esp_camera_fb_get();
        //     if (!fb) {
        //         Serial.println("Errore nella cattura della foto");
        //         return;
        //     }

        //     // Chunk di 2048 byte
        //     const size_t chunkSize = 2048;
        //     size_t offset = 0;
        //     while (offset < fb->len) {
        //         size_t len = min(chunkSize, fb->len - offset);
        //         bool ok = client.publish("camera/response", fb->buf + offset, len);
        //         if (!ok) {
        //             Serial.println("Errore durante publish del chunk");
        //         }
        //         offset += len;
        //         delay(10); // opzionale per evitare congestione
        //     }

        //     esp_camera_fb_return(fb);
        //     Serial.println("Foto inviata via MQTT in chunk.");
        }
    }

};

#endif