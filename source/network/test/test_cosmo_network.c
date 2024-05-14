#include "cosmo_message_types.h"
#include "cosmo_network.h"
#include "mock_cosmo_network_config.h"
#include "unity.h"

#include <stdbool.h>

enum cosmoMessageStatus callback(const struct cosmoNetworkHeader* header)
{
    return COSMO_MESSAGE_STATUS_OK;
}

void setUp(void)
{
    // Set up test environment
}

void tearDown(void)
{
    // Clean up test environment
}

void test_cosmoNetwork_getMessageRoute_found(void)
{
    // Arrange
    const cosmoNode dest = 1;
    struct cosmoNetworkHeader header = {.dest = dest};
    struct cosmoNetworkRoute expectedRoute = {
        .dest = dest,
        .remote = false,
        .callback = NULL,
    };
    struct cosmoNetworkConfig config = {
        .size = 1,
        .table = &expectedRoute,
    };

    cosmoNetwork_getConfig_ExpectAndReturn(config);

    // Act
    struct cosmoNetworkRoute actualRoute;
    enum cosmoMessageStatus status
        = cosmoNetwork_getMessageRoute(&header, &actualRoute);

    // Assert
    TEST_ASSERT_EQUAL(COSMO_MESSAGE_STATUS_OK, status);
    TEST_ASSERT_EQUAL_MEMORY(&expectedRoute, &actualRoute, sizeof(expectedRoute));
}

void test_cosmoNetwork_getMessageRoute_null_header(void)
{
    // Arrange
    struct cosmoNetworkRoute route;

    // Act
    enum cosmoMessageStatus status = cosmoNetwork_getMessageRoute(NULL, &route);

    // Assert
    TEST_ASSERT_EQUAL(COSMO_MESSAGE_STATUS_ERROR, status);
}

void test_cosmoNetwork_routeMessage_local(void)
{
    // Arrange
    const cosmoNode dest = 1;
    struct cosmoNetworkHeader header = {.dest = dest};
    struct cosmoNetworkRoute expectedRoute = {
        .dest = dest,
        .remote = false,
        .callback = NULL,
    };
    struct cosmoNetworkConfig config = {
        .size = 1,
        .table = &expectedRoute,
    };

    cosmoNetwork_getConfig_ExpectAndReturn(config);
    cosmoNetwork_sendLocal_ExpectAndReturn(&header, true);

    // Act
    enum cosmoMessageStatus status = cosmoNetwork_routeMessage(&header);

    // Assert
    TEST_ASSERT_EQUAL(COSMO_MESSAGE_STATUS_OK, status);
}

void test_cosmoNetwork_routeMessage_remote(void)
{
    // Arrange
    const cosmoNode dest = 1;
    struct cosmoNetworkHeader header = {.dest = dest};
    struct cosmoNetworkRoute expectedRoute = {
        .dest = dest,
        .remote = true,
        .callback = callback,
    };
    struct cosmoNetworkConfig config = {
        .size = 1,
        .table = &expectedRoute,
    };

    cosmoNetwork_getConfig_ExpectAndReturn(config);

    // Act
    enum cosmoMessageStatus status = cosmoNetwork_routeMessage(&header);

    // Assert
    TEST_ASSERT_EQUAL(COSMO_MESSAGE_STATUS_OK, status);
}

void test_cosmoNetwork_routeMessage_notfound(void)
{
    // Arrange
    struct cosmoNetworkHeader header = {.dest = 1};
    struct cosmoNetworkRoute expectedRoute = {
        .dest = 2,
        .remote = false,
        .callback = NULL,
    };
    struct cosmoNetworkConfig config = {
        .size = 1,
        .table = &expectedRoute,
    };

    cosmoNetwork_getConfig_ExpectAndReturn(config);

    // Act
    enum cosmoMessageStatus status = cosmoNetwork_routeMessage(&header);

    // Assert
    TEST_ASSERT_EQUAL(COSMO_MESSAGE_STATUS_ERROR, status);
}

void test_cosmoNetwork_routeMessage_null_callback(void)
{
    // Arrange
    const cosmoNode dest = 1;
    struct cosmoNetworkHeader header = {.dest = dest};
    struct cosmoNetworkRoute expectedRoute = {
        .dest = dest,
        .remote = true,
        .callback = NULL,
    };
    struct cosmoNetworkConfig config = {
        .size = 1,
        .table = &expectedRoute,
    };

    cosmoNetwork_getConfig_ExpectAndReturn(config);

    // Act
    enum cosmoMessageStatus status = cosmoNetwork_routeMessage(&header);

    // Assert
    TEST_ASSERT_EQUAL(COSMO_MESSAGE_STATUS_OK, status);
}

// void test_cosmoNetwork_routeMessage_local(void)
// {
//     // Arrange
//     struct cosmoNetworkHeader header;

//     // Act
//     enum cosmoMessageStatus status = cosmoNetwork_routeMessage(&header);

//     // Assert
//     TEST_ASSERT_EQUAL(COSMO_MESSAGE_STATUS_OK, status);
// }

void test_cosmoNetwork_routeMessage_should_return_ERROR_when_header_is_NULL(void)
{
    // Act
    enum cosmoMessageStatus status = cosmoNetwork_routeMessage(NULL);

    // Assert
    TEST_ASSERT_EQUAL(COSMO_MESSAGE_STATUS_ERROR, status);
}
