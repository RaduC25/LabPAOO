cmake_minimum_required(VERSION 3.15)
project(ContBancar LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tema
    src/main.cpp
    src/Account.cpp
)

target_include_directories(tema PRIVATE include)

if(MSVC)
    target_compile_options(tema PRIVATE /W4)
else()
    target_compile_options(tema PRIVATE -Wall -Wextra)
endif()
