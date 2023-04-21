#pragma once

#include <pqxx/pqxx>

namespace sql
{
constexpr std::string_view kConnectionStr = "user=postgres host=localhost port=5432 dbname=bubba target_session_attrs=read-write";

class DbConnection
{
public:
    DbConnection(DbConnection &other) = delete;
    void operator=(const DbConnection &) = delete;
    static std::shared_ptr<pqxx::connection> GetConnection();

private:
    DbConnection();
    ~DbConnection();

    static std::shared_ptr<pqxx::connection> db_connection_;
};

} // namespace sql