#include <mqtt/async_client.h>
#include <iostream>
#include <chrono>
#include <thread>

class callback : public virtual mqtt::callback {
public:
    void message_arrived(mqtt::const_message_ptr message) override {
        std::cout << "Messaggio ricevuto su topic: " << message->get_topic() << "\n"
                << "Payload: " << message->to_string() << std::endl;
    }

    void connected(const std::string& cause) override {
        std::cout << "Connesso con successo al broker MQTT!" << std::endl;
    }

    void connection_lost(const std::string& cause) override {
        std::cout << "Connessione persa: " << cause << std::endl;
    }
};

int main() {
    mqtt::async_client client("tcp://localhost:1883", "subscriber");

    mqtt::connect_options connOpts;

    callback cb;

    client.set_callback(cb);

    try {
        client.connect(connOpts)->wait();

        client.subscribe("arduino/Camera", 1);

        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } catch (const mqtt::exception& e) {
        std::cerr << "MQTT error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}