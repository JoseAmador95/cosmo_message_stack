option(CEEDLING_ENABLE_GCOV "Enable coverage" OFF)
option(CEEDLING_ENABLE_SANITIZER "Enable sanitizer" OFF)
option(CEEDLING_SANITIZER_DEFAULT "Enable sanitizer by default" ON)

if(CEEDLING_ENABLE_GCOV)
    include(${CMAKE_CURRENT_LIST_DIR}/gcov.cmake)
endif()

if(CEEDLING_ENABLE_SANITIZER)
    include(${CMAKE_CURRENT_LIST_DIR}/sanitizer.cmake)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/clangformat.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/unity.cmake)

function(add_unit_test)
    set(options DISABLE_SANITIZER ENABLE_SANITIZER)
    set(oneValueArgs NAME UNIT_TEST TARGET)
    set(multiValueArgs MOCK_HEADERS)
    cmake_parse_arguments(UT "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(UT_DISABLE_SANITIZER AND UT_ENABLE_SANITIZER)
        message(FATAL_ERROR "Cannot enable and disable sanitizer at the same time")
    endif()

    add_executable(${UT_NAME} ${UT_UNIT_TEST})
    target_include_directories(${UT_NAME} PRIVATE ${CMOCK_MOCK_DIR})
    target_link_libraries(${UT_NAME} PRIVATE ${UT_TARGET} cmock unity)

    unset(RUNNER_SOURCE)
    generate_runner(${UT_UNIT_TEST} RUNNER_SOURCE)
    target_sources(${UT_NAME} PRIVATE ${RUNNER_SOURCE})

    foreach(HEADER IN LISTS UT_MOCK_HEADERS)
        unset(MOCK_SOURCE)
        mock_header(${HEADER} MOCK_SOURCE)
        target_sources(${UT_NAME} PRIVATE ${MOCK_SOURCE})
    endforeach()

    if(CEEDLING_ENABLE_GCOV)
        target_add_gcov(${UT_TARGET} PUBLIC)
    endif()

    if(CEEDLING_ENABLE_SANITIZER AND 
       ((CEEDLING_SANITIZER_DEFAULT AND NOT UT_DISABLE_SANITIZER) OR 
        (NOT CEEDLING_SANITIZER_DEFAULT AND UT_ENABLE_SANITIZER)))
        target_add_sanitizer(${UT_TARGET} PUBLIC)
    endif()

    set_target_properties(
        ${UT_NAME}
        PROPERTIES
            C_CLANG_TIDY ""
            CXX_CLANG_TIDY ""
            SKIP_LINTING TRUE
    )

    add_test(NAME ${UT_NAME} COMMAND ${UT_NAME})
endfunction()
