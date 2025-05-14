#include "src/MotorStepper/MotorStepper.hpp"
#include "src/MQTT/Schedule.hpp"
#include "src/MQTT/mqtt.hpp"

int led =  LED_BUILTIN;

//MotorStepper motorStepper(20);

Omqx mqtt;

void setup() {
    Serial.begin(9600);
    
    Omqx::setInstance(&mqtt);  
    mqtt.begin();              
    mqtt.subscribe("raspberry/camera");
}

void loop() {
    mqtt.loop();

    int speed = mqtt.getSpeed();
    int duration = mqtt.getDuration();
    String direction = mqtt.getDirection();
   // motorStepper.step();
}
