#include "client_socket.hpp"

#include <stdexcept>
#include <sys/socket.h>
#include <sstream>
#include <string_view>

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/un.h>

namespace
{
constexpr std::string_view port = "8000";
constexpr size_t max_connections = 5;
}

namespace services
{

ClientSocket::ClientSocket()
{
    addrinfo hints, *res;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    getaddrinfo("localhost", port.data(), &hints, &res);

    client_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (client_fd < 0)
    {
        std::stringstream err_msg;
        err_msg << "Socket creation failed: " << std::strerror(errno) << "\n";
        throw std::runtime_error(err_msg.str());
    }

    int opt = 1;
    if (setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0)
    {
        std::stringstream err_msg;
        err_msg << "Socket setsockopt failed: " << std::strerror(errno) << "\n";
        throw std::runtime_error(err_msg.str());
    }

    if (connect(client_fd, res->ai_addr, res->ai_addrlen) < 0)
    {
        std::stringstream err_msg;
        err_msg << "Socket connect failed: " << std::strerror(errno) << "\n";
        throw std::runtime_error(err_msg.str());
    }

    std::string msg{"Hello from client"};
    if (send(client_fd, msg.c_str(), msg.size() + 1, 0) < 0)
    {
        std::stringstream err_msg;
        err_msg << "Socket send failed: " << std::strerror(errno) << "\n";
        throw std::runtime_error(err_msg.str());
    }
    printf("Hello message sent\n");

}

ClientSocket::~ClientSocket()
{
    std::cerr << "~ClientSocket:\n";
    // shutdown(client_fd, SHUT_RDWR);
    close(client_fd);
}

}