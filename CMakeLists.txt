cmake_minimum_required(VERSION 3.22.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(bubba-server)

include_directories(services/inc)

add_library(
  ${CMAKE_PROJECT_NAME}-lib SHARED
  server_main.cpp services/src/chat_service.cpp services/src/client_socket.cpp
  services/src/server_socket.cpp
)

add_executable(${CMAKE_PROJECT_NAME} server_main.cpp)
target_link_libraries(
  ${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}-lib
)

add_executable(bubba-client client_main.cpp)
target_link_libraries(
  bubba-client ${CMAKE_PROJECT_NAME}-lib
)

option(ENABLE_UNITTESTS "Enable building unit tests" ON)
if(ENABLE_UNITTESTS)
  add_custom_target(run-tests COMMENT "Running All Unittests")
  add_subdirectory(services/tst)
endif(ENABLE_UNITTESTS)
