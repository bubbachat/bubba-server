cmake_minimum_required(VERSION 3.22.0)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(protocol)
target_include_directories(protocol
  PUBLIC
  .
  ${CMAKE_CURRENT_BINARY_DIR}
  ${Protobuf_INCLUDE_DIRS}
)
find_package(Protobuf REQUIRED)
set(PROTO_SOURCES chat_message.proto)
protobuf_generate_cpp(LIB_SOURCES LIB_HEADERS ${PROTO_SOURCES} )
target_link_libraries(protocol ${Protobuf_LIBRARIES})
target_sources(protocol
  PRIVATE
  ${LIB_HEADERS}
  ${LIB_SOURCES}
)
