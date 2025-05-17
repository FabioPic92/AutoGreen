#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <string>

namespace Mqtt {

class MqttClient {
private:
    std::string m_server;
    std::string m_topic;
    int m_port;

public:
    MqttClient(const std::string &server, const std::string &topic, int port)
    :   m_server(server), m_topic(topic), m_port(port)
    {}

};

}

#endif


