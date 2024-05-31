include(ceedling)

add_unit_test(
    NAME test_application
    UNIT_TEST ${PROJECT_SOURCE_DIR}/source/application/test/test_cosmo_application.c
    TARGET ${PROJECT_NAME}_application
    MOCK_HEADERS ${PROJECT_SOURCE_DIR}/source/application/public_inc/cosmo_application_config.h
                 ${PROJECT_SOURCE_DIR}/source/utils/public_inc/cosmo_alloc.h
)

add_unit_test(
    NAME test_network
    UNIT_TEST ${PROJECT_SOURCE_DIR}/source/network/test/test_cosmo_network.c
    TARGET ${PROJECT_NAME}_network
    MOCK_HEADERS ${PROJECT_SOURCE_DIR}/source/network/public_inc/cosmo_network_config.h
                 ${PROJECT_SOURCE_DIR}/source/utils/public_inc/cosmo_alloc.h
)