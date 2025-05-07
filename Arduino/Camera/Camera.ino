#include "src/MotorStepper/MotorStepper.hpp"
#include "src/MQTT/mqtt.hpp"

int led =  LED_BUILTIN;

//MotorStepper motorStepper(20);
Omqx *omqx;

void setup() {
    Serial.begin(9600);
    omqx = new Omqx();
}

void loop() {
    omqx->loop();
   // motorStepper.step();
}
