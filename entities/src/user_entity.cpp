#include "user_entity.hpp"
#include "user_repository.hpp"

#include <iostream>
#include <stdexcept>

namespace entities 
{

UserEntity::UserEntity(std::string name) : name_{name}
{
}

} // namespace entities