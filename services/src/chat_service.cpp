#include "chat_service.hpp"
#include "message_entity.hpp"
#include "message_repository.hpp"
#include "user_entity.hpp"
#include <memory>
#include <unordered_map>

namespace services
{

ChatService::ChatService()
    : user_repository_{std::make_unique<repositories::UserRepository>()}
    , message_repository_{std::make_unique<repositories::MessageRepository>()}
{
}

void ChatService::CheckInUser(std::string name)
{
    user_ = std::make_unique<entities::UserEntity>(name);
    user_repository_->Create(*user_);
    client_socket_ = std::make_unique<services::ClientSocket>(user_->GetId());
}

std::unordered_map<std::string, int> ChatService::GetOnlineUsers()
{
    std::unordered_map<std::string, int> users_map;
    // TODO improve design of trigger async/response for online users
    client_socket_->TriggerUpdateOnlineUsersAsync(user_->GetId());
    auto user_ids = client_socket_->GetOnlineUsers();
    for (const auto &user_id : user_ids) {
        if (user_id != user_->GetId()) {
            auto user = user_repository_->GetById(user_id);
            users_map[user.GetName()] = user_id;
        }
    }
    return users_map;
}

void ChatService::SendMessage(std::string message, int target_user_id)
{
    client_socket_->SendMessage(message, 
        user_->GetName(), user_->GetId(), target_user_id);
    auto message_entity = entities::MessageEntity(message, user_->GetId(), target_user_id);
    message_repository_->Create(message_entity);
}

} // end namespace services
