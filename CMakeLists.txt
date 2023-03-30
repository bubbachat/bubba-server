cmake_minimum_required(VERSION 3.22.0)
project(bubba-server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    services/inc
)

set(SOURCES
    server_main.cpp
    services/src/chat_service.cpp
    services/src/server_socket.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
add_library(${CMAKE_PROJECT_NAME}_lib SHARED ${SOURCES})

add_executable(bubba-client
    client_main.cpp
    services/src/client_socket.cpp
)

option(ENABLE_UNITTESTS "Enable building unit tests" ON)
if (ENABLE_UNITTESTS)
    add_custom_target(run-tests
        COMMENT "Running All Unittests"
    )
    add_subdirectory(services/tst)
endif (ENABLE_UNITTESTS)
