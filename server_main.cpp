#include <iostream>

#include "chat_service.hpp"
#include "server_socket.hpp"


int main(){

	services::ChatService chatService;
	chatService.sendMessage("hello world");

	services::ServerSocket server;

	return 0;
}
