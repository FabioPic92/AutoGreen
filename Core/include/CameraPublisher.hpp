#ifndef MQTT_PUBLISHER_H
#define MQTT_PUBLISHER_H

#include <string>
#include <vector>
#include <mqtt/async_client.h>

class CameraPublisher {
public:
    CameraPublisher(const std::string& address, const std::string& clientId);

    ~CameraPublisher();

    void connect();
    void disconnect();

    bool isConnected() const {
        return m_connected;
    }

    void publish(const std::string& topic, const std::vector<uint8_t>& payload, 
                 int qos = 1, bool retain = false);
    void requestPhoto(const std::string& topic = "camera/request", int qos = 1);
private:
    mqtt::async_client m_client;
    bool m_connected; 
};

#endif 
