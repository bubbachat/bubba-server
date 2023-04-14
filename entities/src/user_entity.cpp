#include "user_entity.hpp"
#include "user_repository.hpp"

#include <iostream>
#include <stdexcept>

namespace entities 
{

UserEntity::UserEntity(std::string name, int id) : name_{name}, id_{id}
{
}

} // namespace entities