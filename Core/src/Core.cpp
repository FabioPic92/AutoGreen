#include "MqttReceiver.hpp"
#include "SensorProcessor.hpp"
#include <thread>

int main() {
    MQTTReceiver receiver("tcp://localhost:1883", "sensors/#");
    receiver.start();

    SensorProcessor processor(receiver);
    std::thread worker(&SensorProcessor::run, &processor);

    worker.join(); 
}