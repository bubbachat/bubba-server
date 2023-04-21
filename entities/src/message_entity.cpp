#include "message_entity.hpp"

#include <iostream>

namespace entities 
{

MessageEntity::MessageEntity(std::string content, int from_id, int to_id)
    : content_{content}, from_id_(from_id), to_id_(to_id)
{
}

} // namespace entities