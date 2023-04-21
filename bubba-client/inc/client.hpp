#pragma once

#include "chat_service.hpp"

#include <iostream>

namespace client
{

constexpr int kInvalidUserId = -1;

class Client
{
public:
    explicit Client();
    int SelectUserToChat();
    void ChatWithUser(int target_user_id);
private:
    std::string name_;
    services::ChatService chat_service_;
};
} // namespace client

