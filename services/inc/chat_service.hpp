#pragma once

#include "user_entity.hpp"

#include <iostream>
#include <vector>

namespace services
{

class ChatService
{
public:
    void checkInUser(std::string name);
    bool sendMessage(std::string message);
private:
    std::vector<entities::UserEntity> checked_in_users_;
};

} // namespace services
