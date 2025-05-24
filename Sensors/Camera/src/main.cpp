#include <Arduino.h>  
#include "Schedule.hpp"
#include "mqtt.hpp"

Omqx mqtt;

void setup() {
    Serial.begin(9600);
    
    Omqx::setInstance(&mqtt);  
    mqtt.begin();              
}

void loop() {
    mqtt.loop();
}