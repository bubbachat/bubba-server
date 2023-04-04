#include "user_entity.hpp"
#include "user_repository.hpp"

#include <iostream>
#include <stdexcept>

namespace entities 
{

UserEntity::UserEntity(std::string name) : name_{name}
{
    repositories::UserRepository user_repository{};
    if (!user_repository.createUser(name))
    {
        throw std::runtime_error("unable to create user");
    };
}

} // namespace entities