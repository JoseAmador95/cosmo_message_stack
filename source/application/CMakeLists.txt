set(COMPONENT_NAME ${PROJECT_NAME}_application)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/public_inc)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

add_library(${COMPONENT_NAME} ${SRC_DIR}/cosmo_application.c)
target_include_directories(${COMPONENT_NAME} PUBLIC ${INC_DIR})
target_link_libraries(${COMPONENT_NAME} PUBLIC ${PROJECT_NAME}_utils)

add_executable(test_application ${TEST_DIR}/test_cosmo_application.c)
target_link_libraries(test_application ${COMPONENT_NAME} cmock unity)