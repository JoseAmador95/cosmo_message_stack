cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(cosmo_message_stack C)

if(PROJECT_IS_TOP_LEVEL)
    include(FetchContent)
    FetchContent_Declare(cmake_toolbox
        GIT_REPOSITORY https://github.com/JoseAmador95/cmake_toolbox.git
        GIT_TAG        main
    )
    FetchContent_MakeAvailable(cmake_toolbox)
endif()

include(clangtidy)
set_clang_tidy(ON)

add_subdirectory(source)

if(PROJECT_IS_TOP_LEVEL)
    enable_testing()
    add_subdirectory(test)
endif()