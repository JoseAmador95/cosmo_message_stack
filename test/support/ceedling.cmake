include(FetchContent)

FetchContent_Declare(
    cmock
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/CMock.git
    GIT_TAG        v2.5.3
)
FetchContent_MakeAvailable(cmock)

FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG        v2.6.0
)
FetchContent_MakeAvailable(unity)

find_package(Ruby REQUIRED)

set(CMOCK_WORK_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(CMOCK_OUTPUT_DIR ${CMOCK_WORK_DIR}/mocks)
set(CMOCK_PRESET mock_)
set(CMOCK_CONFIG ${CMAKE_CURRENT_LIST_DIR}/cmock.yml)
set(CMOCK_EXE ${cmock_SOURCE_DIR}/lib/cmock.rb)
set(RUNNER_OUTPUT_DIR ${CMOCK_WORK_DIR}/runners) 
set(RUNNER_EXE ${unity_SOURCE_DIR}/auto/generate_test_runner.rb)
file(MAKE_DIRECTORY ${CMOCK_OUTPUT_DIR})
file(MAKE_DIRECTORY ${RUNNER_OUTPUT_DIR})

add_library(cmock STATIC ${cmock_SOURCE_DIR}/src/cmock.c)
target_include_directories(cmock PUBLIC ${cmock_SOURCE_DIR}/src)
target_link_libraries(cmock PUBLIC unity)

function(mock_header _header _mock_source)
    cmake_path(GET _header STEM _header_name)
    set(MOCK_SOURCE "${CMOCK_OUTPUT_DIR}/${CMOCK_PRESET}${_header_name}.c")
    add_custom_command(
        OUTPUT "${MOCK_SOURCE}"
        COMMAND ${RUBY_EXECUTABLE} ${CMOCK_EXE} ${_header} -o${CMOCK_CONFIG}
        WORKING_DIRECTORY ${CMOCK_WORK_DIR}
        MAIN_DEPENDENCY ${_header}
        DEPENDS ${CMOCK_CONFIG} 
                ${_header}
                ${RUBY_EXECUTABLE}
        COMMENT "Generate a mock for ${_header}"
    )
    set(${_mock_source} ${MOCK_SOURCE} PARENT_SCOPE)
endfunction()

function(generate_runner _test_source _runner_source)
    cmake_path(GET _test_source STEM _test_name)
    set(RUNNER_SOURCE "${RUNNER_OUTPUT_DIR}/${_test_name}_runner.c")
    add_custom_command(
        OUTPUT "${RUNNER_SOURCE}"
        COMMAND ${RUBY_EXECUTABLE} ${RUNNER_EXE} ${CMOCK_CONFIG} ${_test_source} ${RUNNER_SOURCE}
        DEPENDS ${_test_source} 
                ${CMOCK_CONFIG}
                ${RUBY_EXECUTABLE}
        COMMENT "Generate a test runner for ${_test_source}"
    )
    set(${_runner_source} ${RUNNER_SOURCE} PARENT_SCOPE)
endfunction()

function(add_unit_test)
    set(options)
    set(oneValueArgs NAME UNIT_TEST TARGET)
    set(multiValueArgs MOCK_HEADERS)
    cmake_parse_arguments(UT "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    add_executable(${UT_NAME} ${UT_UNIT_TEST})
    target_include_directories(${UT_NAME} PRIVATE ${CMOCK_OUTPUT_DIR})
    target_link_libraries(${UT_NAME} PRIVATE ${UT_TARGET} cmock unity)

    unset(RUNNER_SOURCE)
    generate_runner(${UT_UNIT_TEST} RUNNER_SOURCE)
    target_sources(${UT_NAME} PRIVATE ${RUNNER_SOURCE})

    foreach(HEADER IN LISTS UT_MOCK_HEADERS)
        unset(MOCK_SOURCE)
        mock_header(${HEADER} MOCK_SOURCE)
        target_sources(${UT_NAME} PRIVATE ${MOCK_SOURCE})
    endforeach()

    add_test(NAME ${UT_NAME} COMMAND ${UT_NAME})
endfunction()