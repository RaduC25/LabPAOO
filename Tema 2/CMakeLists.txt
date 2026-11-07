cmake_minimum_required(VERSION 3.10)
project(tema2 CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tema2
    src/main.cpp
    src/Student.cpp
    src/StudentUnic.cpp
)

target_include_directories(tema2 PRIVATE include)
target_compile_options(tema2 PRIVATE -Wall -Wextra)