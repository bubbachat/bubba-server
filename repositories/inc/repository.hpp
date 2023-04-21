#pragma once

#include <string>

namespace repositories
{

template<typename T>
class IRepository
{
public:
    virtual void Create(T& entity) = 0;
    virtual T GetById(int id) = 0;
    virtual T GetByName(std::string name) = 0;
};

} // namespace repositories
