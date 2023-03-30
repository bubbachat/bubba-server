#include "server_socket.hpp"

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
constexpr size_t BUFFER_SIZE = 100;
}

namespace services
{

ServerSocket::ServerSocket()
{
    addrinfo hints, *res;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    getaddrinfo("localhost", port.data(), &hints, &res);

    server_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (server_fd < 0)
    {
        std::stringstream err_msg;
        err_msg << "Socket creation failed: " << std::strerror(errno) << "\n";
        throw std::runtime_error(err_msg.str());
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0)
    {
        std::stringstream err_msg;
        err_msg << "Socket setsockopt failed: " << std::strerror(errno) << "\n";
        throw std::runtime_error(err_msg.str());
    }

    if (bind(server_fd, res->ai_addr, res->ai_addrlen) < 0)
    {
        std::stringstream err_msg;
        err_msg << "Socket bind failed: " << std::strerror(errno) << "\n";
        throw std::runtime_error(err_msg.str());
    }

    char buffer[BUFFER_SIZE];
    int bytes_read = recv(server_fd, buffer, BUFFER_SIZE, 0);
    if (bytes_read < 0)
    {
        std::stringstream err_msg;
        err_msg << "Socket recv failed: " << std::strerror(errno) << "\n";
        throw std::runtime_error(err_msg.str());
    }
    printf("Message received: %s\n", buffer);
}

ServerSocket::~ServerSocket()
{
    std::cerr << "~ServerSocket:\n";
    // shutdown(server_fd, SHUT_RDWR);
    close(server_fd);
}

}
