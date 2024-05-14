set(COMPONENT_NAME ${PROJECT_NAME}_network)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/public_inc)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

add_library(${COMPONENT_NAME} STATIC
    # ${SRC_DIR}/cosmo_send_network.c
    ${SRC_DIR}/cosmo_network.c
)
target_include_directories(${COMPONENT_NAME} PUBLIC ${INC_DIR})
target_link_libraries(${COMPONENT_NAME} PUBLIC ${PROJECT_NAME}_utils)

add_executable(test_network ${TEST_DIR}/test_cosmo_network.c)
target_link_libraries(test_network ${COMPONENT_NAME} cmock unity)