#pragma once

#include <iostream>
#include <unordered_set>

namespace services
{
class ClientSocket
{
public:
    ClientSocket(int id);
    ~ClientSocket();
    void SendMessage(std::string message, std::string sender_name, int sender_id, int destination_id);
    void TriggerUpdateOnlineUsersAsync(int sender_id);
    std::unordered_set<int> GetOnlineUsers() const { return online_users_; };

private:
    void ReceiveMessage(int client_fd);
    int client_fd_;
    std::unordered_set<int> online_users_;
};
} // namespace services
