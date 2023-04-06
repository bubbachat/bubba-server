#include "user_repository.hpp"

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

void UserRepository::CreateUser(std::string name) 
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
}

void UserRepository::SetUserStatus(std::string name, UserStatus status)
{
    pqxx::work transaction{*db_connection_};
    std::string update_str = "UPDATE " + kTableName + " SET present='" + std::to_string(static_cast<bool>(status)) + \
                                "' WHERE username='" + name  + "'";
    transaction.exec(update_str);
    transaction.commit();
}

std::vector<std::string> UserRepository::GetOnlineUsers()
{
    std::vector<std::string> users;
    pqxx::work transaction{*db_connection_};
    for (const auto [name] : transaction.query<std::string>("SELECT username FROM users where present='1'"))
    {
        users.push_back(name);
    }
    return users;
}

} // namespace repositories 