#pragma once

#include <iostream>

namespace services
{

class ChatService 
{
public:
    bool sendMessage(std::string message);
};

} // end namespace servicecs