#pragma once

#include <iostream>
#include <pqxx/pqxx>

namespace repositories
{

const std::string kDbHostName = "localhost";
const std::string kDbName = "bubba";
const std::string kDbPort = "5432";
const std::string kDbUser = "postgres";
const std::string kTableName = "users";

class UserRepository
{
public:
    explicit UserRepository();
    [[nodiscard]] bool createUser(std::string name);
private:
    std::unique_ptr<pqxx::connection> db_connection_;
};

} // namespace repositories