#include <iostream>

#include "chat_service.hpp"

int main(){
	
	services::ChatService chatService;
	chatService.sendMessage("hello world");

	return 0;
}