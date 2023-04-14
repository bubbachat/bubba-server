#pragma once

#include <unordered_map>

namespace services
{
class ServerSocket
{
public:
    ServerSocket();
    ~ServerSocket();

private:
    void ProcessClientRequest(int client_connection_fd);
    int server_fd;
    std::unordered_map<int, int> client_map_;
};
} // namespace services
