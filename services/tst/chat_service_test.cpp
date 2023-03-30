#include <iostream>

#include "gtest/gtest.h"

#include "chat_service.hpp"

TEST(ChatServiceTests, send_message)
{
    services::ChatService chatService;

    auto result = chatService.sendMessage("42");

    EXPECT_TRUE(result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}