#include <iostream>

#include <mqtt/async_client.h>
#include <json.hpp> 

namespace Mqtt {

enum Direction{
    FORWARD,
    REVERSE
};


struct CommandMessage {
    int8_t m_step;            
    uint16_t m_duration;      
    Direction m_direction;
    
    CommandMessage(int8_t step, uint16_t duration, Direction direction) 
    :   m_step(step), m_duration(duration), m_direction(direction)
    {}
};

int main() {
    mqtt::async_client client("tcp://localhost:1883", "publisher");
    mqtt::connect_options connOpts;

    CommandMessage commandMessage(100, 3000, Direction::FORWARD);

    int payload = 10;

     std::string payload_str = std::to_string(payload);

    try {
        client.connect(connOpts)->wait();
        auto msg = mqtt::make_message("raspberry/camera", payload_str);
        client.publish(msg)->wait();
        client.disconnect()->wait();
        std::cout << "Published!" << std::endl;
    } catch (const mqtt::exception& e) {
        std::cerr << "MQTT error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

}