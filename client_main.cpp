#include <iostream>

#include "chat_service.hpp"
#include "client_socket.hpp"


int main(){
	std::string username;
	std::cout << "Enter your name" << std::endl;
	std::cin >> username;
	services::ChatService chat_service;
	chat_service.checkInUser(username);

	services::ClientSocket client;

	return 0;
}
