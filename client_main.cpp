#include <iostream>

#include "chat_service.hpp"
#include "client_socket.hpp"

int main(){
	std::string username;
	std::cout << "Enter your name" << std::endl;
	std::cin >> username;

	services::ChatService chat_service;
	chat_service.CheckInUser(username);

	while (1)
	{
		std::cout << "-----Bubba----" << std::endl;
		std::cout << "Users online: " << std::endl;
		auto users = chat_service.GetOnlineUsers();
		for (const auto &user : users)
		{
			std::cout << user.GetName() << std::endl;
		}
		std::cout << "------------" << std::endl;
		std::cout << "Select one user to chat from the list above by name or press [\\r] to refresh:" << std::endl;
		std::string target_user;
		std::cin >> target_user;
		if (target_user == "\\r") continue;
		
		std::cout << "------------" << std::endl;
		std::cout << "Starting chat with " << target_user << ", press [\\q] to return or type message below" << std::endl;
		std::string message;
		while (message != "\\q")
		{
			std::cout << std::endl;
			std::getline(std::cin, message);
			if (message != "\\q")
				chat_service.SendMessage(message, target_user);
		}
	} 

	return 0;
}
