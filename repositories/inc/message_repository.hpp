#pragma once

#include "message_entity.hpp"
#include "repository.hpp"
#include <iostream>
#include <pqxx/pqxx>
#include <vector>

namespace repositories
{

class MessageRepository
{
public:
    explicit MessageRepository();
    virtual void Create(entities::MessageEntity& entity);
private:
    const std::string kTableName = "messages";
};

} // namespace repositories