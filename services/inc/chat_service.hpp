#pragma once


#include "client_socket.hpp"
#include "message_repository.hpp"
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
    std::unordered_map<std::string, int> GetOnlineUsers();
    void SendMessage(std::string message, int target_user_id);
private:
    std::unique_ptr<services::ClientSocket> client_socket_;
    std::unique_ptr<repositories::UserRepository> user_repository_;
    std::unique_ptr<repositories::MessageRepository> message_repository_;
    std::unique_ptr<entities::UserEntity> user_;
};

} // namespace services
