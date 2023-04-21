#include "db_connection.hpp"
#include <memory>
#include <iostream>

namespace sql
{

std::shared_ptr<pqxx::connection> DbConnection::db_connection_ = nullptr;

std::shared_ptr<pqxx::connection> DbConnection::GetConnection()
{
    if (db_connection_ == nullptr)
    {
        db_connection_ = std::make_shared<pqxx::connection>(kConnectionStr.data());
    }
    return db_connection_;
}

} // namespace sql
