#pragma once

#include <iostream>
#include <pqxx/pqxx>
#include <vector>

namespace repositories
{

const std::string kDbHostName = "localhost";
const std::string kDbName = "bubba";
const std::string kDbPort = "5432";
const std::string kDbUser = "postgres";

enum class UserStatus : bool
{
    kOnline = true,
    kOffline = false
};

class UserRepository
{
public:
    explicit UserRepository();
    void CreateUser(std::string name);
    void SetUserStatus(std::string name, UserStatus status);
    std::vector<std::string> GetOnlineUsers();
private:
    std::unique_ptr<pqxx::connection> db_connection_;
    const std::string kTableName = "users";
};

} // namespace repositories