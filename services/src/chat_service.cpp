#include "chat_service.hpp"

namespace services
{

ChatService::ChatService() : user_repository_{std::make_unique<repositories::UserRepository>()}
{
}

void ChatService::CheckInUser(std::string name)
{
    client_socket_ = std::make_unique<services::ClientSocket>();
    user_ = std::make_unique<entities::UserEntity>(name);
    user_repository_->CreateUser(name);
    user_repository_->SetUserStatus(name, repositories::UserStatus::kOnline);
}

std::vector<entities::UserEntity> ChatService::GetOnlineUsers()
{
    std::vector<entities::UserEntity> users{};
    auto names = user_repository_->GetOnlineUsers();

    for (const auto &name : names) 
    {
        if (name != user_->GetName())
            users.push_back(entities::UserEntity(name));
    }

    return users;
}

bool ChatService::SendMessage(std::string message)
{
    std::cout << "sending message " << message << std::endl;

    return true;
}

} // end namespace services
