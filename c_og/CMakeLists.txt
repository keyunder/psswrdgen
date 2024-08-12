cmake_minimum_required(VERSION 3.30)
project(psswrdgen)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")

add_executable(${PROJECT_NAME} src/main.c)