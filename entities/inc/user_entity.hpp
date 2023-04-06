#pragma once

#include <iostream>

namespace entities
{

class UserEntity 
{
public:
    explicit UserEntity(std::string name);
    std::string GetName() const { return name_; };

private:
    std::string name_;
};

} // namespace entities