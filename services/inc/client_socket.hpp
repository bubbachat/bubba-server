#pragma once

#include <iostream>

namespace services
{
class ClientSocket
{
public:
    ClientSocket(int id);
    ~ClientSocket();
    void SendMessage(std::string message, std::string sender_name, int sender_id, int destination_id);

private:
    void ReceiveMessage(int client_fd);
    int client_fd;
};
} // namespace services
