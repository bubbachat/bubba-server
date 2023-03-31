#include "server_socket.hpp"

#include <sstream>
#include <stdexcept>
#include <string_view>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

namespace
{
constexpr std::string_view address = "localhost";
constexpr std::string_view port = "8000";
constexpr size_t max_connections = 1;
constexpr size_t BUFFER_SIZE = 100;
} // namespace

namespace services
{

ServerSocket::ServerSocket()
{
    addrinfo hints, *res;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(address.data(), port.data(), &hints, &res);

    if (int status = getaddrinfo(address.data(), port.data(), &hints, &res);
        status != 0)
    {
        std::stringstream err_msg;
        err_msg << "Socket getaddrinfo failed: " << gai_strerror(status)
                << "\n";
        throw std::runtime_error(err_msg.str());
    }

    server_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (server_fd < 0)
    {
        std::stringstream err_msg;
        err_msg << "Socket creation failed: " << std::strerror(errno) << "\n";
        throw std::runtime_error(err_msg.str());
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt)) < 0)
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

    if (listen(server_fd, max_connections) < 0)
    {
        std::stringstream err_msg;
        err_msg << "Socket listen failed: " << std::strerror(errno) << "\n";
        throw std::runtime_error(err_msg.str());
    }

    sockaddr_storage client_addr;
    socklen_t client_addr_size;
    int client_connection_fd =
        accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_size);
    if (client_connection_fd < 0)
    {
        std::stringstream err_msg;
        err_msg << "Socket listen failed: " << std::strerror(errno) << "\n";
        throw std::runtime_error(err_msg.str());
    }

    char buffer[BUFFER_SIZE];
    int bytes_read = recv(client_connection_fd, buffer, BUFFER_SIZE, 0);
    if (bytes_read < 0)
    {
        std::stringstream err_msg;
        err_msg << "Socket recv failed: " << std::strerror(errno) << "\n";
        throw std::runtime_error(err_msg.str());
    }
    std::cerr << "Message received: " << buffer << "\n";
}

ServerSocket::~ServerSocket()
{
    std::cerr << "~ServerSocket:\n";
    close(client_connection_fd);
    close(server_fd);
}

} // namespace services
