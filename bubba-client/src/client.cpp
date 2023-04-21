#include "client.hpp"

namespace client {

Client::Client()
{
	std::cout << "Enter your name below:" << std::endl;
	std::getline(std::cin, name_);
	chat_service_.CheckInUser(name_);
}

int Client::SelectUserToChat()
{
	int target_user_id = kInvalidUserId;
    std::cout << "-----Bubba----" << std::endl;
	std::cout << "Users online: " << std::endl;
	auto online_users = chat_service_.GetOnlineUsers();

	for (const auto &online_user : online_users)
		std::cout << online_user.first << std::endl;

	std::cout << "------------" << std::endl;
	std::cout << "Select one user to chat from the list above by name or press [\\r] to refresh:" << std::endl;
	std::string target_user;
	std::getline(std::cin, target_user);
	
    if (target_user == "\\r")
    {
        return target_user_id;
    }
    else if (online_users.find(target_user) == online_users.end())
    {
        std::cerr << "User " <<  target_user << " not found" << std::endl;
    }
    else
    {
        std::cout << "------------" << std::endl;
	    std::cout << "Starting chat with " << target_user << ", press [\\q] to return or type message below" << std::endl;
        target_user_id = online_users[target_user];
    }
    
    return target_user_id;
}

void Client::ChatWithUser(int target_user_id)
{
    std::string message;
    while (message != "\\q")
    {
        std::cout << std::endl;
        std::getline(std::cin, message);
        if (message != "\\q")
            chat_service_.SendMessage(message, target_user_id);
    }
}

} // namespace client
