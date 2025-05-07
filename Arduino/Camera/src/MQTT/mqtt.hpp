#ifndef MQTT_H
#define MQTT_H

#include <WiFi.h>          // Libreria WiFi per ESP32
#include <PubSubClient.h>  // Libreria MQTT

const char* ssid = "A54";
const char* password = "onow5432";

// Configurazione MQTT
const char* mqttServer = "192.168.77.85 ";  
const int mqttPort = 1883;
const char* mqttUser = "admin";  
const char* mqttPassword = "public";  

class Omqx {
private:

        WiFiClient espClient;
        PubSubClient client;

public:

    Omqx() : client(espClient) 
    {
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

        Serial.println("WiFi connesso");
        Serial.print("Indirizzo IP: ");
        Serial.println(WiFi.localIP());
    }

    static void callback(char* topic, byte* payload, unsigned int length) {
      Serial.print("Messaggio ricevuto su topic: ");
      Serial.println(topic);

      Serial.print("Messaggio: ");
      for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
      }
      Serial.println();
    }

    void reconnect() {
      while (!client.connected()) {
        Serial.print("Connessione al broker MQTT...");

        // Tentativi di connessione
        if (client.connect("ESP32Client", mqttUser, mqttPassword)) {
          Serial.println("Connesso al broker MQTT!");
          // Sottoscrizione al topic
          client.subscribe("arduino/camera");
        } else {
          Serial.print("Errore di connessione, rc=");
          Serial.print(client.state());
          delay(5000);  // Attende 5 secondi prima di riprovare
        }
        Serial.print("\n");
      }
    }

    void loop(){
      if (!client.connected()) {
        reconnect();
      }
      client.loop();
    }
};

#endif


// void loop() {
//   if (!client.connected()) {
//     reconnect();
//   }
//   client.loop();
// }