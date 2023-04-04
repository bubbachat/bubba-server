#pragma once

#include <iostream>

namespace entities
{

class UserEntity 
{
public:
    explicit UserEntity(std::string name);

private:
    std::string name_;
};

} // namespace entities