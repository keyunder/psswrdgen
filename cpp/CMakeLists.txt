cmake_minimum_required(VERSION 3.30)
project(psswrdgen)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

add_executable(${PROJECT_NAME} src/main.cpp)