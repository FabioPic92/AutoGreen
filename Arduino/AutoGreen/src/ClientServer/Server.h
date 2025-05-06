#include <string>

#include "WiFiS3.h"
#include "arduino_secrets.h" 

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;  

namespace UnoR4 {

class Server {
  private:
    int m_status = WL_IDLE_STATUS;
    std::string fireware;
    WiFiServer *server;

  public:
    Server(int status) : m_status(status){
      server = new WiFiServer(80);
      server->begin();
    }

    int Connection(){
      if (WiFi.status() == WL_NO_MODULE) {
        Serial.println("Communication with WiFi module failed!");
        return -1;
      }

      fireware = WiFi.firmwareVersion();

      if (fireware < WIFI_FIRMWARE_LATEST_VERSION) {
        Serial.println("Please upgrade the firmware");
      }

      while (m_status != WL_CONNECTED) {
        Serial.print("Attempting to connect to Network named: ");
        Serial.println(ssid);                

        m_status = WiFi.begin(ssid, pass);

        delay(10000);
      }
      server->begin();
      Serial.println("Connection Successful");    
      return 0;
    }  

    void printWifiStatus() {
      Serial.print("SSID: ");
      Serial.println(WiFi.SSID());
      IPAddress ip = WiFi.localIP();
      Serial.print("IP Address: ");
      Serial.println(ip);

      long rssi = WiFi.RSSI();
      Serial.print("signal strength (RSSI):");
      Serial.print(rssi);
      Serial.println(" dBm");

      Serial.print("To see this page in action, open a browser to http://");
      Serial.println(ip);

    }

    bool isConnected() {
        return WiFi.status() == WL_CONNECTED;
    }

    WiFiServer *getServer(){
      return server;
    }
};

}