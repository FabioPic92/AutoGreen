#include "SensorProcessor.hpp"
#include <iostream>

SensorProcessor::SensorProcessor(MQTTReceiver& receiver)
    : m_receiver(receiver) {}

void SensorProcessor::run() {
    while (true) {
        std::pair<std::string, std::string> msg;
        if (m_receiver.get_next_message(msg)) {
            // 🔍 ESEMPIO: elaborazione messaggio
            std::cout << "🔧 Elaboro " << msg.first << ": " << msg.second << std::endl;

            // 👇 Qui puoi fare parsing JSON, calcoli, scrittura DB, ecc.
            // if (msg.first == "sensors/temperature") { ... }
        }
    }
}