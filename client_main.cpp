#include <iostream>

#include "client.hpp"

int main(){
	
	client::Client client;

	while (1)
	{
		auto target_user_id = client.SelectUserToChat();
		if (target_user_id != client::kInvalidUserId)
		{
			client.ChatWithUser(target_user_id);
		}
	} 

	return 0;
}


