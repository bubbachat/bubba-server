#pragma once


#include "client_socket.hpp"
#include "user_entity.hpp"
#include "user_repository.hpp"

#include <iostream>
#include <vector>
#include <memory>

namespace services
{

class ChatService
{
public:
    explicit ChatService();
    void CheckInUser(std::string name);
    std::vector<entities::UserEntity> GetOnlineUsers();
    void SendMessage(std::string message, std::string target_user);
private:
    std::unique_ptr<services::ClientSocket> client_socket_;
    std::unique_ptr<repositories::UserRepository> user_repository_;
    std::unique_ptr<entities::UserEntity> user_;
};

} // namespace services
