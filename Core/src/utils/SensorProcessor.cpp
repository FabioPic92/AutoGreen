#include "SensorProcessor.hpp"
#include <iostream>

SensorProcessor::SensorProcessor(MQTTReceiver& receiver)
    : m_receiver(receiver) {}

void SensorProcessor::run() {
    while (true) {
        std::pair<std::string, std::string> msg;
        if (m_receiver.get_next_message(msg)) {
            //implemented code
        }
    }
}