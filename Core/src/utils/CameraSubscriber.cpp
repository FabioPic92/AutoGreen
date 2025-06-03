#include "CameraSubscriber.hpp"

#include <iostream>

CameraSubscriber::CameraSubscriber(const std::string& address, const std::string& topic)
    : m_client(address, "ReceiverClient"), m_topic(topic) {
    m_client.set_callback(*this);
}

void CameraSubscriber::start() {
    mqtt::connect_options conn_opts;
    conn_opts.set_clean_session(true);
    m_client.connect(conn_opts)->wait();
    m_client.subscribe(m_topic, 1)->wait();
    std::cout << "Connect to" << m_topic << std::endl;
}

void CameraSubscriber::message_arrived(mqtt::const_message_ptr msg) {
    std::lock_guard<std::mutex> lock(m_mutex);

    std::string topic = msg->get_topic();
    const void* payload = msg->get_payload().data();
    size_t len = msg->get_payload().size();

    std::vector<uint8_t> data((uint8_t*)payload, (uint8_t*)payload + len);

    m_queue.emplace(topic, std::move(data));
    m_cv.notify_one();
}

bool CameraSubscriber::get_next_message(std::pair<std::string, std::vector<uint8_t>>& out) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cv.wait(lock, [&]{ return !m_queue.empty(); });

    out = m_queue.front();
    m_queue.pop();
    return true;
}
