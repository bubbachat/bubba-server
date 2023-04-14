#include "server_socket.hpp"

#include "chat_message.pb.h"

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
#include <thread>

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

    (void) getaddrinfo(address.data(), port.data(), &hints, &res);

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

    while (1)
    {
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

        std::thread th(&ServerSocket::ProcessClientRequest, this, client_connection_fd);
        th.detach();
    }
}

ServerSocket::~ServerSocket()
{
    std::cerr << "~ServerSocket:\n";
    for (const auto &client : client_map_) close(client.second);
    close(server_fd);
}

void ServerSocket::ProcessClientRequest(int client_connection_fd)
{
    char buffer[BUFFER_SIZE];
    while (int bytes_read = recv(client_connection_fd, buffer, sizeof(buffer),0) != 0)
    {
        if (bytes_read < 0)
        {
            std::stringstream err_msg;
            err_msg << "Socket recv failed: " << std::strerror(errno) << "\n";
            throw std::runtime_error(err_msg.str());
        }

        protocol::ChatMessage rcv_message;
        rcv_message.ParseFromString(buffer);

        auto sender_id = rcv_message.sender_id();
        if (client_map_.find(sender_id) == client_map_.end())
            client_map_[sender_id] = client_connection_fd;

        protocol::ChatMessage dst_message;
        if (rcv_message.has_destination_id()) 
        {
            int destination_connection_fd = client_map_[rcv_message.destination_id()];

            dst_message.set_sender_id(rcv_message.sender_id());
            dst_message.set_sender_name(rcv_message.sender_name());
            dst_message.set_msg(rcv_message.msg());
            
            auto msg = dst_message.SerializeAsString();
            
            if (send(destination_connection_fd, msg.c_str(), msg.size() + 1, 0) < 0)
            {
                std::stringstream err_msg;
                err_msg << "Socket send failed: " << std::strerror(errno) << "\n";
                throw std::runtime_error(err_msg.str());
            }
        } else {
            // send back online users
            dst_message.set_sender_id(rcv_message.sender_id());
            for (const auto &client : client_map_) {
                auto user = dst_message.add_online_users();
                user->set_user_id(client.first); 
            }
            
            auto msg = dst_message.SerializeAsString();
            
            if (send(client_connection_fd, msg.c_str(), msg.size() + 1, 0) < 0)
            {
                std::stringstream err_msg;
                err_msg << "Socket send failed: " << std::strerror(errno) << "\n";
                throw std::runtime_error(err_msg.str());
            }
        }

    }
}

} // namespace services
