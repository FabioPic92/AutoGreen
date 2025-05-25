#include "wifi.hpp"
#include "camera_web.hpp"
#include "camera_mqtt.hpp"

CameraWeb *cameraWeb;
CameraMQTT cameraMqtt;

void setup() {
  Serial.begin(115200);

  connectWifi();

  cameraWeb = new CameraWeb(cameraMqtt); 
  cameraWeb->begin(); 
}

void loop() {
  cameraWeb->loop();
  cameraMqtt.loop();
}