#include "WiFiS3.h"

namespace UnoR4 {

class Client {
  WiFiClient m_client;
  WiFiServer* m_server;


  public:
    Client(WiFiServer* server) : m_server(server){
      InitClient();
    }

    void InitClient() {
      if(m_server != nullptr) {
        m_client = m_server->available();
      }
      else {
        Serial.println("Client not found");
      }
    }

    int Connection() {
      if (m_client) {                       
        Serial.println("new client"); 
        String currentLine = ""; 

        while (m_client.connected()) {
          if (m_client.available()) {             // if there's bytes to read from the client,
            char c = m_client.read();             // read a byte, then
            Serial.write(c);                    // print it out to the serial monitor
            if (c == '\n') {                    // if the byte is a newline character
              if (currentLine.length() == 0) {
                m_client.println("HTTP/1.1 200 OK");
                m_client.println("Content-type:text/html");
                m_client.println();

                m_client.print("<p style=\"font-size:7vw;\">Click <a href=\"/H\">here</a> turn the LED on<br></p>");
                m_client.print("<p style=\"font-size:7vw;\">Click <a href=\"/L\">here</a> turn the LED off<br></p>");

                m_client.println();
                break;
              } else {
                currentLine = "";
              }
            } else if (c != '\r') {  
              currentLine += c;
            }
            if (currentLine.endsWith("GET /H")) {
             digitalWrite(LED_BUILTIN, HIGH);
            }
            if (currentLine.endsWith("GET /L")) {
              digitalWrite(LED_BUILTIN, LOW);              
            }
          }
        }
        Close();
      }
    }

    void Close(){
      m_client.stop();
      Serial.println("client disconnected");
    }
};

}