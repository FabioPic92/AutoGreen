#ifndef WIFI_CAMERA_H
#define WIFI_CAMERA_H

#include <WebServer.h>
#include <WiFi.h>
#include "camera_utils.hpp"
#include "camera_mqtt.hpp"

WebServer server(80);

const char* topicRequest = "camera/request";
const char* topicResponse = "camera/response";

class CameraWeb {
public:
    CameraWeb(const CameraMQTT& cameraMqtt)
    :   m_cameraMQTT(cameraMqtt)
    {
        initCamera();
    }

    void begin() {
        startCameraServer(); 
    }

    void loop() {
        server.handleClient();
    }

private:
    CameraMQTT m_cameraMQTT;

    void startCameraServer() {
        server.on("/", HTTP_GET, []() {
            String html = R"rawliteral(
            <html>
                <head>
                <title>ESP32-CAM</title>
                </head>
                <body>
                <h2>ESP32 Video Stream</h2>
                <img src="/stream" width="320" /><br/><br/>
                <button onclick="fetch('/sendphoto')">Scatta e invia via MQTT</button>
                </body>
            </html>
            )rawliteral";
            server.send(200, "text/html", html);
        });

        server.on("/stream", HTTP_GET, []() {
            WiFiClient client = server.client();
            String response = "HTTP/1.1 200 OK\r\n";
            response += "Content-Type: multipart/x-mixed-replace; boundary=frame\r\n\r\n";
            server.sendContent(response);

            while (client.connected()) {
            camera_fb_t * fb = esp_camera_fb_get();
            if (!fb) continue;

            response = "--frame\r\n";
            response += "Content-Type: image/jpeg\r\n\r\n";
            server.sendContent(response);
            server.sendContent((const char *)fb->buf, fb->len);
            server.sendContent("\r\n");

            esp_camera_fb_return(fb);
            }
        });

        server.on("/sendphoto", HTTP_GET, [this]() {
            const char* payload = "1";  // semplice trigger
            m_cameraMQTT.publish((const uint8_t*)payload, strlen(payload), "camera/request");
            server.send(200, "text/plain", "Richiesta inviata via MQTT");
        });

        server.begin();
        Serial.println("HTTP server started");
    }

};

#endif