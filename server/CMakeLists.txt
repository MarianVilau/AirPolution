cmake_minimum_required(VERSION 3.22.1)
project(sensors_receiver)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
include_directories(include/)
add_executable(${CMAKE_PROJECT_NAME}
  main.cpp
  src/sensors_server.cpp
  src/thread_poll.cpp
  src/mongodb_handler.cpp
)
find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)
include_directories(
    ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/bsoncxx/v_noabi
    ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/mongocxx/v_noabi
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE mongo::mongocxx_shared)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE mongo::mongocxx_shared)