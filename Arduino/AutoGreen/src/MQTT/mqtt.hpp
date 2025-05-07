#include <WiFiS3.h>        // Libreria per WiFiS3
#include <PubSubClient.h>   // Libreria MQTT

const char* ssid = "your-SSID";              // Nome della tua rete WiFi
const char* password = "your-PASSWORD";      // Password della tua rete WiFi

const char* mqttServer = "192.168.1.100";    // IP del Raspberry Pi con EMQX
const int mqttPort = 1883;                   // Porta MQTT

WiFiS3Class wifi;                            // Oggetto WiFi
WiFiClient wifiClient;                       // Client WiFi
PubSubClient mqttClient(wifiClient);         // Client MQTT

void setup() {
  // Inizializzazione seriale
  Serial.begin(115200);
  
  // Connessione WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connessione a WiFi...");
  }
  Serial.println("Connesso a WiFi!");

  // Connessione al broker MQTT
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(mqttCallback);
}

void loop() {
  // Verifica se il client MQTT è connesso, altrimenti riconnetti
  if (!mqttClient.connected()) {
    reconnect();
  }
  
  mqttClient.loop();  // Gestisce la comunicazione MQTT
}

void reconnect() {
  while (!mqttClient.connected()) {
    Serial.print("Tentativo di connessione MQTT...");
    
    // Genera un client ID casuale
    String clientId = "ArduinoClient-";
    clientId += String(random(0xffff), HEX);
    
    // Tenta di connettersi al broker MQTT
    if (mqttClient.connect(clientId.c_str())) {
      Serial.println("Connesso a MQTT!");
      mqttClient.subscribe("arduino/topic");  // Sottoscrizione al topic
    } else {
      Serial.print("Errore di connessione MQTT, stato: ");
      Serial.println(mqttClient.state());
      delay(5000);
    }
  }
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  // Callback quando riceviamo un messaggio
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println("Messaggio ricevuto: " + message);
}
