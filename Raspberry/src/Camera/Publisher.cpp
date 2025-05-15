#include <iostream>

#include <mqtt/async_client.h>
#include <json.hpp> 

int main() {
    mqtt::async_client client("tcp://localhost:1883", "publisher");
    mqtt::connect_options connOpts;

    nlohmann::json jsonMsg;
    jsonMsg["speed"] = 100;
    jsonMsg["duration"] = 3000;
    jsonMsg["direction"] = "forward";

    std::string payload = jsonMsg.dump(); 

    try {
        client.connect(connOpts)->wait();
        std::cout << "Invio messaggio: " << payload << std::endl;
        auto msg = mqtt::make_message("raspberry/camera", payload);
        client.publish(msg)->wait();
        client.disconnect()->wait();
        std::cout << "Published!" << std::endl;
    } catch (const mqtt::exception& e) {
        std::cerr << "MQTT error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}