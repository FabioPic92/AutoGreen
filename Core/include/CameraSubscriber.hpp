#ifndef MQTT_SUBSCRIBER_H
#define MQTT_SUBSCRIBER_H

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <mqtt/async_client.h>

class CameraSubscriber : public virtual mqtt::callback {
public:
    CameraSubscriber(const std::string& address, const std::string& topic);
    
    void start();
    bool get_next_message(std::pair<std::string, std::vector<uint8_t>>& out);

private:
    mqtt::async_client m_client;
    std::string m_topic;

    std::queue<std::pair<std::string, std::vector<uint8_t>>> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cv;

    void message_arrived(mqtt::const_message_ptr msg) override;
};

#endif