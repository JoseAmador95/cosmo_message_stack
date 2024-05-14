include(FetchContent)

FetchContent_Declare(
    ceedling
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Ceedling.git
    GIT_TAG        v0.31.1
)

FetchContent_MakeAvailable(ceedling)

add_subdirectory(${ceedling_SOURCE_DIR}/vendor/unity ${ceedling_BINARY_DIR}/vendor/unity)

set(CMOCK_SRC_DIR ${ceedling_SOURCE_DIR}/vendor/cmock/src)
add_library(cmock STATIC ${CMOCK_SRC_DIR}/cmock.c)
target_include_directories(cmock PUBLIC ${CMOCK_SRC_DIR} ${PROJECT_BINARY_DIR}/ceedling/test/mocks)
target_link_libraries(cmock PUBLIC unity)