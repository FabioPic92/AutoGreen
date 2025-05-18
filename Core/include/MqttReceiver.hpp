#ifndef MQTT_RECEIVER_H
#define MQTT_RECEIVER_H

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <mqtt/async_client.h>

class MQTTReceiver : public virtual mqtt::callback {
public:
    MQTTReceiver(const std::string& address, const std::string& topic);
    void start();

    bool get_next_message(std::pair<std::string, std::string>& out);

private:
    mqtt::async_client m_client;
    std::string m_topic;

    std::queue<std::pair<std::string, std::string>> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cv;

    void message_arrived(mqtt::const_message_ptr msg) override;
};

#endif