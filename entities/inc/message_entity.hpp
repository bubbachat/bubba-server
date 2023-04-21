#pragma once

#include <iostream>

namespace entities
{

class MessageEntity
{
public:
    explicit MessageEntity(std::string content, int from_id, int to_id);
    std::string GetContent() const { return content_; };
    int GetFromId() const { return from_id_; };
    int GetToId() const { return to_id_; };

private:
    std::string content_;
    int from_id_;
    int to_id_;
};

} // namespace entities