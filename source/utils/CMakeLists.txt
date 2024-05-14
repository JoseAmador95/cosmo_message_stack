set(COMPONENT_NAME ${PROJECT_NAME}_utils)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/public_inc)

add_library(${COMPONENT_NAME} STATIC ${SRC_DIR}/cosmo_alloc.c)
target_include_directories(${COMPONENT_NAME} PUBLIC ${INC_DIR})