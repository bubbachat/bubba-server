#include "user_repository.hpp"

#include <iostream>
#include <pqxx/connection.hxx>
#include <pqxx/pqxx>

namespace repositories 
{

UserRepository::UserRepository()
{
    try 
    {
        std::string connection_str = "user = " + repositories::kDbUser + \
                " host=" + repositories::kDbHostName + " port=" + repositories::kDbPort + \
                " dbname=" + repositories::kDbName + " target_session_attrs=read-write";

        db_connection_ = std::make_unique<pqxx::connection>(connection_str);

        if (db_connection_->is_open())
        {
            std::cout << "db connection successful" << std::endl;
        }
        else
        {
            std::cerr << "connection to db could not be established" << std::endl;
            throw std::runtime_error("unable to open connection to database");
        }
    }
    catch (const std::exception &e) 
    {
        std::cerr << e.what() << std::endl;
    }
}

bool UserRepository::createUser(std::string name) 
{
    pqxx::work work_transaction(*db_connection_);
    std::string insert_str = "INSERT INTO " + kTableName + "(username) VALUES ('" + name + "')";
    work_transaction.exec(insert_str);
    work_transaction.commit();

    return true;
}

} // namespace repositories 