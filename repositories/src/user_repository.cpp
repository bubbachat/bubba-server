#include "user_repository.hpp"
#include "user_entity.hpp"

#include <pqxx/connection.hxx>
#include <pqxx/pqxx>

namespace repositories 
{

UserRepository::UserRepository()
{
    std::string connection_str = "user = " + repositories::kDbUser + \
            " host=" + repositories::kDbHostName + " port=" + repositories::kDbPort + \
            " dbname=" + repositories::kDbName + " target_session_attrs=read-write";
    db_connection_ = std::make_unique<pqxx::connection>(connection_str);
}

int UserRepository::CreateOrGetUser(std::string name) 
{
    pqxx::work transaction(*db_connection_);
    pqxx::result res = transaction.exec("SELECT * FROM users where username='" + name + "'");

    if (res.size() == 0)
    {
        std::string insert_str = "INSERT INTO " + kTableName + " (username, present) VALUES ('" + name + "','" + \
                                    std::to_string(static_cast<bool>(UserStatus::kOnline)) + "')";
        transaction.exec(insert_str);
        transaction.commit();
    }

    return transaction.query_value<int>(
                "SELECT id FROM users WHERE username='" + name + "'");
}

void UserRepository::SetUserStatus(std::string name, UserStatus status)
{
    pqxx::work transaction{*db_connection_};
    std::string update_str = "UPDATE " + kTableName + " SET present='" + std::to_string(static_cast<bool>(status)) + \
                                "' WHERE username='" + name  + "'";
    transaction.exec(update_str);
    transaction.commit();
}

int UserRepository::GetUserIdByName(std::string name)
{
    pqxx::work transaction{*db_connection_};
    return transaction.query_value<int>("SELECT id FROM users where username='" + name + "'");
}

entities::UserEntity UserRepository::GetUserById(int id)
{
    pqxx::work transaction{*db_connection_};
    auto username = 
        transaction.query_value<std::string>("SELECT username FROM users where id='" + std::to_string(id) + "'");
    return entities::UserEntity(username, id);
}

} // namespace repositories 