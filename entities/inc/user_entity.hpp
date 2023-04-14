#pragma once

#include <iostream>

namespace entities
{

class UserEntity 
{
public:
    explicit UserEntity(std::string name, int id);
    std::string GetName() const { return name_; };
    int GetId() const { return id_; };

private:
    std::string name_;
    int id_;
};

} // namespace entities