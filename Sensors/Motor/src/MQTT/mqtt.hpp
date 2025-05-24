#ifndef MQTT_H
#define MQTT_H

#include "../struct.hpp"

#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "A54";
const char* password = "onow5432";

const char* mqttServer = "192.168.180.85";
const int mqttPort = 1883;
const char* mqttUser = "admin";
const char* mqttPassword = "public";

typedef void (*MessageCallback)(uint16_t step, uint16_t duration, Direction direction);

String getMacAddress() {
    uint8_t mac[6];
    WiFi.macAddress(mac); 
    char macStr[18];   
    snprintf(macStr, sizeof(macStr),
             "%02X:%02X:%02X:%02X:%02X:%02X",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return String(macStr);
}

class Omqx {
private:
    WiFiClient espClient;
    PubSubClient client;

    uint16_t m_receivedSpeed = 0;
    uint16_t m_receivedDuration = 0;
    Direction m_receivedDirection;

    static MessageCallback userCallback;

public:
    Omqx() : client(espClient) 
    {
    }

    void begin() {
        setupWifi();
        client.setServer(mqttServer, mqttPort);
        client.setCallback(callbackWrapper);
    }

    void setupWifi() {
        delay(10);
        Serial.println("\nConnecting to WiFi...");
        WiFi.begin(ssid, password);

        while(WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        Serial.println(WiFi.localIP());
    }

    void reconnect() {
        while(!client.connected()) {
            Serial.println("Connetting to broker MQTT...");
            String clientId = "Motor-" + getMacAddress();
            if (client.connect(clientId.c_str(), mqttUser, mqttPassword)) {
                Serial.println("Connected!");
                subscribe("core/Motor");
            } else {
                Serial.print(client.state());
                delay(5000);
            }
        }
    }

    void subscribe(const char* topic) {
        if(client.connected()) {
            client.subscribe(topic);
            Serial.print("Subscribe on topic: ");
            Serial.println(topic);
        }
    }

    void publish(const char* topic, const char* message) {
        if(client.connected()) {
            client.publish(topic, message);
            Serial.print("Pubblic on");
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

    int getSpeed() const { return m_receivedSpeed; }
    int getDuration() const { return m_receivedDuration; }
    Direction getDirection() const { return m_receivedDirection; }

    static void setMessageCallback(MessageCallback cb) {
        userCallback = cb;
    }

private:

    static void callbackWrapper(char* topic, byte* payload, unsigned int length) {
        instance->handleCallback(topic, payload, length);
    }

    void handleCallback(char* topic, byte* payload, unsigned int length) {
        Serial.print("Messagge receive on topic: ");
        Serial.println(topic);

        uint16_t step = payload[0] | (payload[1] << 8);
        uint16_t duration = payload[2] | (payload[3] << 8);
        uint8_t directionVal = payload[4];    

        m_receivedSpeed = step;
        m_receivedDuration = duration;
        m_receivedDirection = (directionVal == 0) ? FORWARD : REVERSE;

        if (userCallback) {
            userCallback(step, duration, (directionVal == 0) ? FORWARD : REVERSE);
        }
    }

    static Omqx* instance;

public:
    static void setInstance(Omqx* inst) {
        instance = inst;
    }
};

Omqx* Omqx::instance = nullptr;
MessageCallback Omqx::userCallback = nullptr;

#endif