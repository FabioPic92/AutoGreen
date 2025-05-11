#pragma once

#include <string>

#include <boost/mqtt5/mqtt_client.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/detached.hpp>

class Client {
private:
    std::string m_serverAddress;
    std::string m_clientID;
    std::string m_topic;

public:
    Client(const std::string &serverAddress, const std::string &clientID, const std::string &topic)
    : m_serverAddress(serverAddress),
      m_clientID(clientID),
      m_topic(topic)
    {}

    virtual void loop() = 0;

};

class ClientCamera : public Client {

};

void mqtt(){
  boost::asio::io_context ioc;

  boost::mqtt5::mqtt_client<boost::asio::ip::tcp::socket> client(ioc);


}
