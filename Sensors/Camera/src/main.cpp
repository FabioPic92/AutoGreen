#include "wifi.hpp"
#include "camera_web.hpp"
#include "camera_mqtt.hpp"
#include "camera_web.hpp"

CameraWeb *cameraWeb;
CameraMQTT cameraMqtt;

void setup() {
  Serial.begin(115200);

  connectWifi();

  cameraMqtt.begin();

  cameraWeb = new CameraWeb(cameraMqtt); 
  cameraWeb->begin(); 

  initCamera();

}

void loop() {
  cameraWeb->loop();
  cameraMqtt.loop();
}