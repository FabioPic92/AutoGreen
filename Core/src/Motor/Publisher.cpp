#include <iostream>

#include <mqtt/async_client.h>

enum Direction{
    FORWARD,
    REVERSE
};

struct MessagePayload {
    uint16_t m_step;            
    uint16_t m_duration;      
    Direction m_direction;
    
    MessagePayload(uint16_t step, uint16_t duration, Direction direction) 
    :   m_step(step), m_duration(duration), m_direction(direction)
    {}

    std::string serialize() const {
        char buffer[5];
        buffer[0] = m_step & 0xFF;
        buffer[1] = (m_step >> 8) & 0xFF;  
        buffer[2] = m_duration & 0xFF;         
        buffer[3] = (m_duration >> 8) & 0xFF; 
        buffer[4] = static_cast<uint8_t>(m_direction);
        return std::string(buffer, 5);
    }
};

int main(int argc, char *argv[]) {
    mqtt::async_client client("tcp://localhost:1883", "publisher");
    mqtt::connect_options connOpts;

    if(argc > 4) {
        std::cout << "Error" << std::endl;
    }

    unsigned long lStep = std::strtoul(argv[1], nullptr, 10);
    unsigned long lDuration = std::strtoul(argv[2], nullptr, 10);

    uint16_t step = static_cast<uint16_t>(lStep);
    uint16_t duration = static_cast<uint16_t>(lDuration);


    Direction direction = (std::string(argv[3]) == "REVERSE") ? Direction::REVERSE : Direction::FORWARD;

    std::cout << "Data send" << std::endl;
    std::cout << step << " " << duration << " " << direction << std::endl;

    MessagePayload messagePayload(step, duration, direction);

    std::string Payload = messagePayload.serialize();

    try {
        client.connect(connOpts)->wait();
        auto msg = mqtt::make_message("core/Motor", Payload);
        client.publish(msg)->wait();
        client.disconnect()->wait();
        std::cout << "Published!" << std::endl;
    } catch (const mqtt::exception& e) {
        std::cerr << "MQTT error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
