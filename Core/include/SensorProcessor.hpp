#ifndef SENSOR_PROCESSOR_H
#define SENSOR_PROCESSOR_H

#include "MqttReceiver.hpp"

class SensorProcessor {
public:
    SensorProcessor(MQTTReceiver& receiver);
    void run();

private:
    MQTTReceiver& m_receiver;
};

#endif