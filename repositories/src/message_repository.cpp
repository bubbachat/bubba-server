#include "db_connection.hpp"
#include "message_repository.hpp"
#include "message_entity.hpp"

#include <memory>
#include <pqxx/connection.hxx>
#include <pqxx/pqxx>
#include <string>

namespace repositories 
{

MessageRepository::MessageRepository()
{
}

void MessageRepository::Create(entities::MessageEntity& entity) 
{
    pqxx::work transaction{*sql::DbConnection::GetConnection()};
    std::string insert_str = "INSERT INTO " + kTableName + " (content, from_id, to_id) VALUES ('" + entity.GetContent() + "','" \
        + std::to_string(entity.GetFromId()) + "','" + std::to_string(entity.GetToId()) + "')";
    transaction.exec(insert_str);
    transaction.commit();
}

} // namespace repositories 