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
    auto users = user_repository_->GetOnlineUsers();
    users.erase(std::remove_if(users.begin(), users.end(),
                             [&](entities::UserEntity& user) { return user.GetId() == user_->GetId(); }));
    return users;
}

void ChatService::SendMessage(std::string message, std::string name)
{
    auto target_id = user_repository_->GetUserIdByName(name);
    client_socket_->SendMessage(message, 
        user_->GetName(), user_->GetId(), target_id);
}

} // end namespace services
