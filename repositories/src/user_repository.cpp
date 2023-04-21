#include "db_connection.hpp"
#include "user_repository.hpp"
#include "user_entity.hpp"

#include <memory>
#include <pqxx/connection.hxx>
#include <pqxx/pqxx>

namespace repositories 
{

UserRepository::UserRepository()
{
}

void UserRepository::Create(entities::UserEntity& entity) 
{
    pqxx::work transaction{*sql::DbConnection::GetConnection()};
    pqxx::result res = transaction.exec("SELECT * FROM users where username='" + entity.GetName() + "'");
    if (res.size() == 0)
    {
        std::string insert_str = "INSERT INTO " + kTableName + " (username) VALUES ('" + entity.GetName() + "')";
        transaction.exec(insert_str);
    }
    auto user_id = transaction.query_value<int>(
                "SELECT id FROM users WHERE username='" + entity.GetName() + "'");
    transaction.commit();
    entity.SetId(user_id);
}

entities::UserEntity UserRepository::GetByName(std::string name)
{
    pqxx::work transaction{*sql::DbConnection::GetConnection()};
    auto id = transaction.query_value<int>("SELECT id FROM users where username='" + name + "'");
    return entities::UserEntity(name, id);
}

entities::UserEntity UserRepository::GetById(int id)
{
    pqxx::work transaction{*sql::DbConnection::GetConnection()};
    auto name = 
        transaction.query_value<std::string>("SELECT username FROM users where id='" + std::to_string(id) + "'");
    return entities::UserEntity(name, id);
}

} // namespace repositories 