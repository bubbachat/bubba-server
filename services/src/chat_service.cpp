#include "chat_service.hpp"
#include "user_entity.hpp"

namespace services
{

ChatService::ChatService() : user_repository_{std::make_unique<repositories::UserRepository>()}
{
}

void ChatService::CheckInUser(std::string name)
{
    auto id = user_repository_->CreateOrGetUser(name);
    user_ = std::make_unique<entities::UserEntity>(name, id);
    client_socket_ = std::make_unique<services::ClientSocket>(id);
    user_repository_->SetUserStatus(name, repositories::UserStatus::kOnline);
}

std::vector<entities::UserEntity> ChatService::GetOnlineUsers()
{
    std::vector<entities::UserEntity> users;
    // TODO improve design of trigger async/response for online users
    client_socket_->TriggerUpdateOnlineUsersAsync(user_->GetId());
    auto user_ids = client_socket_->GetOnlineUsers();
    for (const auto &user_id : user_ids) {
        if (user_id != user_->GetId()) {
            auto user = user_repository_->GetUserById(user_id);
            users.push_back(user);
        }
    }
    return users;
}

void ChatService::SendMessage(std::string message, std::string name)
{
    auto target_id = user_repository_->GetUserIdByName(name);
    client_socket_->SendMessage(message, 
        user_->GetName(), user_->GetId(), target_id);
}

} // end namespace services
