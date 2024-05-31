cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(C_CLANG_TIDY "clang-tidy")

project(cosmo_message_stack C)

add_subdirectory(source)

if(PROJECT_IS_TOP_LEVEL)
    enable_testing()
    add_subdirectory(test)
endif()