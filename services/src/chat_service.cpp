#include "chat_service.hpp"

namespace services
{

bool ChatService::sendMessage(std::string message)
{
    std::cout << "sending message " << message << std::endl;

    return true;
}

} // end namespace services
