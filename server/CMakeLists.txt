cmake_minimum_required(VERSION 3.22.1)
project(sensors_receiver)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
include_directories(include/)
add_executable(${CMAKE_PROJECT_NAME}
  main.cpp
  src/sensors_server.cpp
  src/thread_poll.cpp
)