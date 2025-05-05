#include "WiFiS3.h"

namespace UnoR4 {

class Client {
  WiFiClient m_client;
  WiFiServer *m_server;


  public:
    Client(WiFiServer *server) : m_server(server){
      InitClient();
    }

    int InitClient() {
      if(m_server != nullptr) {
        m_client = m_server->available();
      }
      else {
        Serial.println("Client not found");
        return -1;
      }
      return 0;
    }

    int Connection() {
      if (m_client) {                       
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

                m_client.println("<form action=\"/data\" method=\"GET\">");
                m_client.println("<label for=\"valore\">Inserisci un valore:</label>");
                m_client.println("<input type=\"text\" id=\"valore\" name=\"valore\">");
                m_client.println("<input type=\"submit\" value=\"Invia\">");
                m_client.println("</form>");

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
            if (currentLine.startsWith("GET /data?valore=")) {
                int start = currentLine.indexOf("=") + 1;
                int end = currentLine.indexOf(" ", start); 
                String value = currentLine.substring(start, end);

                Close();
                return value.toInt();
            }
          }
        }
        Close();
        return 0;
      }
      return -1;
    }

    bool isConnected() {
        return m_client && m_client.connected();
    }

    void Close(){
      m_client.stop();
      Serial.println("client disconnected");
    }
};

}