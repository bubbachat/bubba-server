#include <iostream>

#include "chat_service.hpp"
#include "server_socket.hpp"


int main(){

	services::ChatService chatService;
	chatService.SendMessage("hello world");

	services::ServerSocket server;

	return 0;
}
