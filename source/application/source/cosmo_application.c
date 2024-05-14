/**
 * @file cosmo_application.c
 * @brief This file contains the implementation of the Cosmo Application.
 */

#include "cosmo_application.h"

#include "cosmo_alloc.h"
#include "cosmo_application_config.h"
#include "cosmo_message_status.h"

#include <string.h>

enum cosmoMessageStatus cosmoMessage_allocate(
    struct cosmoMessageHeader* header,
    cosmoMsgId msgId,
    cosmoNode source,
    cosmoNode dest,
    const void* payload,
    size_t size
)
{
    enum cosmoMessageStatus status = COSMO_MESSAGE_STATUS_OK;

    if (NULL != header)
    {
        header->source = source;
        header->dest = dest;
        header->msgId = msgId;
        header->payload = NULL;
        header->size = 0U;

        if (size > 0U)
        {
            void* ptr = cosmo_malloc(size);

            if (NULL != ptr && NULL != payload)
            {
                memcpy(ptr, payload, size);
                header->payload = ptr;
                header->size = size;
            }
            else
            {
                status = COSMO_MESSAGE_MALLOC_FAILED;
            }
        }
    }
    else
    {
        status = COSMO_MESSAGE_STATUS_ERROR;
    }

    return status;
}

enum cosmoMessageStatus cosmoMessage_allocateAndSend(
    cosmoMsgId msgId,
    cosmoNode source,
    cosmoNode dest,
    const void* payload,
    size_t size
)
{
    struct cosmoMessageHeader header;
    enum cosmoMessageStatus status
        = cosmoMessage_allocate(&header, msgId, source, dest, payload, size);

    if (COSMO_MESSAGE_STATUS_OK == status)
    {
        status = cosmoMessage_send(&header);
    }

    if (header.payload != NULL)
    {
        cosmo_free((void*) header.payload);
    }

    return status;
}
