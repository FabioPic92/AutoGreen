#include "MqttReceiver.hpp"
#include <iostream>

MQTTReceiver::MQTTReceiver(const std::string& address, const std::string& topic)
    : m_client(address, "ReceiverClient"), m_topic(topic) {
    m_client.set_callback(*this);
}

void MQTTReceiver::start() {
    mqtt::connect_options conn_opts;
    conn_opts.set_clean_session(true);
    m_client.connect(conn_opts)->wait();
    m_client.subscribe(m_topic, 1)->wait();
    std::cout << "Connect to" << m_topic << std::endl;
}

void MQTTReceiver::message_arrived(mqtt::const_message_ptr msg) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_queue.emplace(msg->get_topic(), msg->to_string());
    m_cv.notify_one();
}

bool MQTTReceiver::get_next_message(std::pair<std::string, std::string>& out) {
    std::unique_lock<std::mutex> lock(m_mutex);
    if (m_queue.empty()) {
        m_cv.wait(lock, [&]{ return !m_queue.empty(); });
        return false;
    } else {
        out = m_queue.front();
        m_queue.pop();
        return true;
    }
    return false;
}
