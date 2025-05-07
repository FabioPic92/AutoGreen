#include <WiFiS3.h>        // Libreria per WiFiS3
#include <PubSubClient.h>   // Libreria MQTT

const char* ssid = "your-SSID";              // Nome della tua rete WiFi
const char* password = "your-PASSWORD";      // Password della tua rete WiFi

const char* mqttServer = "192.168.1.100";    // IP del Raspberry Pi con EMQX
const int mqttPort = 1883;                   // Porta MQTT


WiFiClient espClient;
PubSubClient client(espClient);

// Ricezione messaggio MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Ricevuto su topic [");
  Serial.print(topic);
  Serial.print("]: ");

  String message = "";
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.println(message);

  // Puoi convertire in intero se serve
  int number = message.toInt();
  Serial.print("Numero ricevuto: ");
  Serial.println(number);
}

void setup_wifi() {
  delay(100);
  Serial.print("Connessione a WiFi ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connesso.");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connessione al broker MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Connesso!");
      client.subscribe(topic);
    } else {
      Serial.print("Errore: ");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}