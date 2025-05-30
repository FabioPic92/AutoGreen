#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 8080

class WebServer {
private:
    int m_serverFd, m_socket;
    long m_valread;
    struct sockaddr_in m_address;
    int m_addrlen;

public:
    WebServer() {
        m_addrlen = sizeof(m_address);

    }

};

#endif
