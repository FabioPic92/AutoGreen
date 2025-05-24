#include "src/MotorStepper/MotorStepper.hpp"
#include "src/Schedule/Schedule.hpp"
#include "src/MQTT/mqtt.hpp"

Omqx mqtt;
Schedule schedule;

void setup() {
    Serial.begin(9600);
            
    Omqx::setInstance(&mqtt); 
    Omqx::setMessageCallback(Schedule::handleMqttMessage); 
    mqtt.begin();   
}

void loop() {
    mqtt.loop(); 

    if(!schedule.isEmpty()){
        schedule.execute();
    }
}
