#include "CameraPublisher.hpp"

#include <iostream>
#include <stdexcept>

CameraPublisher::CameraPublisher(const std::string& address, const std::string& clientId)
    : m_client(address, clientId), m_connected(false) {
    // You can optionally set a callback here if you want to handle connection/delivery events,
    // but for a simple publisher, it's often not strictly necessary unless you need specific acknowledgments.
    // m_client.set_callback(...);
}

CameraPublisher::~CameraPublisher() {
    if (m_connected) {
        disconnect();
    }
}

void CameraPublisher::connect() {
    mqtt::connect_options conn_opts;
    conn_opts.set_clean_session(true);

    try {
        std::cout << "Attempting to connect to MQTT broker at " << m_client.get_server_uri() << "..." << std::endl;
        m_client.connect(conn_opts)->wait();
        m_connected = true;
        std::cout << "Successfully connected to MQTT broker." << std::endl;
    } catch (const mqtt::exception& exc) {
        std::cerr << "Error connecting to MQTT broker: " << exc.what() << std::endl;
        m_connected = false;
        throw std::runtime_error("Failed to connect to MQTT broker.");
    }
}

void CameraPublisher::disconnect() {
    if (m_connected) {
        try {
            std::cout << "Attempting to disconnect from MQTT broker..." << std::endl;
            m_client.disconnect()->wait();
            m_connected = false;
            std::cout << "Successfully disconnected from MQTT broker." << std::endl;
        } catch (const mqtt::exception& exc) {
            std::cerr << "Error disconnecting from MQTT broker: " << exc.what() << std::endl;
        }
    }
}

void CameraPublisher::publish(const std::string& topic, const std::vector<uint8_t>& payload, int qos, bool retain) {
    if (!m_connected) {
        std::cerr << "Error: Not connected to MQTT broker. Cannot publish message." << std::endl;
        return;
    }

    try {
        mqtt::message_ptr pubmsg = mqtt::make_message(topic, payload.data(), payload.size());
        pubmsg->set_qos(qos);
        pubmsg->set_retained(retain);

        m_client.publish(pubmsg)->wait();
        std::cout << "Message published to topic: '" << topic << "' (Payload size: " << payload.size() << " bytes)." << std::endl;
    } catch (const mqtt::exception& exc) {
        std::cerr << "Error publishing message: " << exc.what() << std::endl;
    }
}

void CameraPublisher::requestPhoto(const std::string& topic, int qos) {
    if (!m_connected) {
        std::cerr << "Error: Not connected to MQTT broker. Cannot request photo." << std::endl;
        return;
    }

    try {
        // Send an empty payload, or a small string like "REQUEST" if you prefer
        // The ESP32-CAM code only checks the topic, so the payload content isn't critical for the request itself.
        mqtt::message_ptr pubmsg = mqtt::make_message(topic, ""); // Empty payload
        pubmsg->set_qos(qos);
        pubmsg->set_retained(false);

        m_client.publish(pubmsg)->wait();
        std::cout << "Photo request sent to topic: '" << topic << "'." << std::endl;
    } catch (const mqtt::exception& exc) {
        std::cerr << "Error sending photo request: " << exc.what() << std::endl;
    }
}

// #include "CameraPublisher.hpp"
// #include <iostream>
// #include <thread> // For std::this_thread::sleep_for
// #include <chrono> // For std::chrono::seconds

// int main() {
//     CameraPublisher publisher("tcp://192.168.180.85:1883", "MyCameraRequester");

//     try {
//         publisher.connect();

//         // Request a photo
//         publisher.requestPhoto("camera/request");

//         // In a real application, you might then set up a subscriber
//         // to listen for the "camera/response" topic to receive the image data.
//         // For demonstration, we'll just disconnect after a short delay.
//         std::this_thread::sleep_for(std::chrono::seconds(5)); // Give ESP32 time to respond

//         publisher.disconnect();

//     } catch (const std::runtime_error& e) {
//         std::cerr << "Application error: " << e.what() << std::endl;
//         return 1;
//     } catch (...) {
//         std::cerr << "An unknown error occurred." << std::endl;
//         return 1;
//     }

//     return 0;
// }