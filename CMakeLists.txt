cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(cosmo_message_stack C)
enable_testing()

add_subdirectory(source)

if(PROJECT_IS_TOP_LEVEL)
    add_subdirectory(test)
endif()