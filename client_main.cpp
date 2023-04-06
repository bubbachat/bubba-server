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
		std::cout << "Select one user to chat from the list above by name:" << std::endl;
		std::string target_user;
		std::cin >> target_user;
		// TODO: continue
	}

	return 0;
}
