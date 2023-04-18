#include "client_socket.hpp"

#include "chat_message.pb.h"

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <thread>

namespace
{
constexpr std::string_view server_address = "localhost";
constexpr std::string_view server_port = "8000";
constexpr size_t BUFFER_SIZE = 100;
const std::string green("\033[1;32m");
const std::string reset("\033[0m");
} // namespace

namespace services
{

ClientSocket::ClientSocket(int id)
{
    addrinfo hints, *res;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (int status = getaddrinfo(server_address.data(), server_port.data(), &hints, &res); status != 0)
    {
        std::stringstream err_msg;
        err_msg << "Socket getaddrinfo failed: " << gai_strerror(status) << "\n";
        throw std::runtime_error(err_msg.str());
    }

    client_fd_ = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (client_fd_ < 0)
    {
        std::stringstream err_msg;
        err_msg << "Socket creation failed: " << std::strerror(errno) << "\n";
        throw std::runtime_error(err_msg.str());
    }

    int opt = 1;
    if (setsockopt(client_fd_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0)
    {
        std::stringstream err_msg;
        err_msg << "Socket setsockopt failed: " << std::strerror(errno) << "\n";
        throw std::runtime_error(err_msg.str());
    }

    if (connect(client_fd_, res->ai_addr, res->ai_addrlen) < 0)
    {
        std::stringstream err_msg;
        err_msg << "Socket connect failed: " << std::strerror(errno) << "\n";
        throw std::runtime_error(err_msg.str());
    }

    protocol::ChatMessage connect_msg;
    connect_msg.set_sender_id(id);
    auto msg = connect_msg.SerializeAsString();

    if (send(client_fd_, msg.c_str(), msg.size() + 1, 0) < 0)
    {
        std::stringstream err_msg;
        err_msg << "Socket send failed: " << std::strerror(errno) << "\n";
        throw std::runtime_error(err_msg.str());
    }

    std::thread th(&ClientSocket::ReceiveMessage, this, client_fd_);

    th.detach();
}

void ClientSocket::SendMessage(std::string message, std::string sender_name, int sender_id, int destination_id)
{

    protocol::ChatMessage snd_msg;
    snd_msg.set_sender_id(sender_id);
    snd_msg.set_destination_id(destination_id);
    snd_msg.set_sender_name(sender_name);
    snd_msg.set_msg(message);

    auto msg = snd_msg.SerializeAsString();

    if (send(client_fd_, msg.c_str(), msg.size() + 1, 0) < 0)
    {
        std::stringstream err_msg;
        err_msg << "Socket send failed: " << std::strerror(errno) << "\n";
        throw std::runtime_error(err_msg.str());
    }
}

void ClientSocket::TriggerUpdateOnlineUsersAsync(int sender_id)
{

    protocol::ChatMessage snd_msg;
    snd_msg.set_sender_id(sender_id);

    auto msg = snd_msg.SerializeAsString();

    if (send(client_fd_, msg.c_str(), msg.size() + 1, 0) < 0)
    {
        std::stringstream err_msg;
        err_msg << "Socket send failed: " << std::strerror(errno) << "\n";
        throw std::runtime_error(err_msg.str());
    }
}

ClientSocket::~ClientSocket()
{
    std::cerr << "~ClientSocket:\n";
    close(client_fd_);
}

void ClientSocket::ReceiveMessage(int client_fd)
{
    char buffer[BUFFER_SIZE];
    while (int bytes_read = recv(client_fd, buffer, sizeof(buffer), 0) != 0)
    {
        if (bytes_read < 0)
        {
            std::stringstream err_msg;
            err_msg << "Socket recv failed: " << std::strerror(errno) << "\n";
            throw std::runtime_error(err_msg.str());
        }
        protocol::ChatMessage rcv_msg;
        rcv_msg.ParseFromString(buffer);

        auto users = rcv_msg.online_users();
        for (auto &user : users)
        {
            online_users_.insert(user.user_id());
        }

        if (rcv_msg.has_msg())
            std::cout << green << rcv_msg.sender_name() << ": " << reset << rcv_msg.msg() << "\n";
    }
    std::cout << "Server disconnected" << std::endl;
}

} // namespace services
