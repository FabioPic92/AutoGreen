#include "MotorStepper.hpp"
#include "Schedule.hpp"
#include "mqtt.hpp"

int led =  LED_BUILTIN;

MotorStepper motorStepper(20);

Omqx mqtt;

void setup() {
    Serial.begin(9600);
     
}

void loop() {

    motorStepper.step();
}
