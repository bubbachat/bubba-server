project(services-unittest)

include(FetchContent)

# ##############################################################################
# GTest
# ##############################################################################
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.8.0
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

# ##############################################################################
# Unit Tests
# ##############################################################################
set(SOURCES chat_service_test.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE ${CMAKE_PROJECT_NAME}-lib gtest gtest_main
)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

add_custom_target(
  run-${PROJECT_NAME}
  COMMENT "Running Bubba Services Unittests"
  COMMAND ${PROJECT_NAME}
)
add_dependencies(run-${PROJECT_NAME} ${PROJECT_NAME})
add_dependencies(run-tests run-${PROJECT_NAME})

add_test(${PROJECT_NAME} ${PROJECT_NAME})
