#include "MqttReceiver.hpp"
#include <iostream>

MQTTReceiver::MQTTReceiver(const std::string& address, const std::string& topic)
    : client(address, "ReceiverClient"), topic_(topic) {
    client.set_callback(*this);
}

void MQTTReceiver::start() {
    mqtt::connect_options conn_opts;
    conn_opts.set_clean_session(true);
    client.connect(conn_opts)->wait();
    client.subscribe(topic_, 1)->wait();
    std::cout << "✅ Connesso a " << topic_ << std::endl;
}

void MQTTReceiver::message_arrived(mqtt::const_message_ptr msg) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.emplace(msg->get_topic(), msg->to_string());
    cv_.notify_one();
}

bool MQTTReceiver::get_next_message(std::pair<std::string, std::string>& out) {
    std::unique_lock<std::mutex> lock(mutex_);
    if (queue_.empty()) {
        cv_.wait(lock, [&]{ return !queue_.empty(); });
    }
    if (!queue_.empty()) {
        out = queue_.front();
        queue_.pop();
        return true;
    }
    return false;
}
