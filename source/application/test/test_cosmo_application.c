#include "cosmo_application.h"
#include "cosmo_message_status.h"
#include "mock_cosmo_alloc.h"
#include "mock_cosmo_application_config.h"
#include "unity.h"

#include <stdlib.h>
#include <string.h>

void setUp(void)
{
    // Set up any necessary resources before each test
}

void tearDown(void)
{
    // Clean up any resources after each test
}

void test_cosmoMessage_allocateAndSend(void)
{
    // Arrange
    struct cosmoMessageHeader header;
    cosmoMsgId msgId = 1;
    cosmoNode source = 2;
    cosmoNode dest = 3;
    const void* payload = "test payload";
    size_t size = strlen(payload) + 1;
    void* ptr = malloc(size);

    // Expectations
    cosmo_malloc_ExpectAndReturn(size, ptr);
    cosmoMessage_send_ExpectAnyArgsAndReturn(COSMO_MESSAGE_STATUS_OK);
    cosmo_free_Expect((void*) ptr);

    // Act
    enum cosmoMessageStatus status
        = cosmoMessage_allocateAndSend(msgId, source, dest, payload, size);

    // Assert
    TEST_ASSERT_EQUAL(COSMO_MESSAGE_STATUS_OK, status);
    free(ptr);
}

void test_cosmoMessage_allocateAndSend_NullMalloc(void)
{
    // Arrange
    struct cosmoMessageHeader header;
    cosmoMsgId msgId = 1;
    cosmoNode source = 2;
    cosmoNode dest = 3;
    const void* payload = "test payload";
    size_t size = strlen(payload) + 1;
    void* ptr = NULL;
    // Expectations
    cosmo_malloc_ExpectAndReturn(size, ptr);
    // Act
    enum cosmoMessageStatus status
        = cosmoMessage_allocateAndSend(msgId, source, dest, payload, size);

    // Assert
    TEST_ASSERT_EQUAL(COSMO_MESSAGE_MALLOC_FAILED, status);
}

void test_cosmoMessage_allocateAndSend_NullPayload(void)
{
    // Arrange
    struct cosmoMessageHeader header;
    cosmoMsgId msgId = 1;
    cosmoNode source = 2;
    cosmoNode dest = 3;
    const void* payload = NULL;
    size_t size = 0;
    // Expectations
    cosmoMessage_send_ExpectAnyArgsAndReturn(COSMO_MESSAGE_STATUS_OK);
    // Act
    enum cosmoMessageStatus status
        = cosmoMessage_allocateAndSend(msgId, source, dest, payload, size);

    // Assert
    TEST_ASSERT_EQUAL(COSMO_MESSAGE_STATUS_OK, status);
}

void test_cosmoMessage_allocateAndSend_NullHeader(void)
{
    // Arrange
    cosmoMsgId msgId = 1;
    cosmoNode source = 2;
    cosmoNode dest = 3;
    const void* payload = "test payload";
    size_t size = strlen(payload) + 1;
    // Act
    enum cosmoMessageStatus status
        = cosmoMessage_allocate(NULL, msgId, source, dest, payload, size);

    // Assert
    TEST_ASSERT_EQUAL(COSMO_MESSAGE_STATUS_ERROR, status);
}