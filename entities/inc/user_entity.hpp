#pragma once

#include <iostream>

namespace entities
{

class UserEntity
{
public:
    explicit UserEntity(std::string name, int id = 0);
    std::string GetName() const { return name_; };
    int GetId() const { return id_; };
    void SetId(int id) { id_ = id; };

private:
    std::string name_;
    int id_;
};

} // namespace entities