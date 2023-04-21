#pragma once

#include "repository.hpp"
#include "user_entity.hpp"
#include <iostream>
#include <pqxx/pqxx>
#include <vector>

namespace repositories
{

class UserRepository : public IRepository<entities::UserEntity>
{
public:
    explicit UserRepository();
    virtual void Create(entities::UserEntity& entity);
    entities::UserEntity GetByName(std::string name);
    entities::UserEntity GetById(int id);
private:
    const std::string kTableName = "users";
};

} // namespace repositories