#include "chat_service.hpp"
#include "user_entity.hpp"

namespace services
{

void ChatService::checkInUser(std::string name)
{
    checked_in_users_.push_back(entities::UserEntity(name));
}

bool ChatService::sendMessage(std::string message)
{
    std::cout << "sending message " << message << std::endl;

    return true;
}

} // end namespace services
