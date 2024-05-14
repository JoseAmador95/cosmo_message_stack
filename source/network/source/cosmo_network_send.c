#include "cosmo_alloc.h"
#include "cosmo_application.h"
#include "cosmo_message_network.h"
#include "cosmo_message_status.h"
#include "cosmo_message_types.h"

#include <string.h>

struct networkMessagePayload
{
    cosmoMsgId msgId;
    const void* payload;
    cosmoPayloadSize size;
};

enum cosmoMessageStatus cosmoMessage_send(struct cosmoMessageHeader* header)

{
    enum cosmoMessageStatus status = COSMO_MESSAGE_STATUS_OK;

    if (NULL != header)
    {
        const struct networkMessagePayload networkPayload = {
            .msgId = header->msgid,
            .payload = header->payload,
            .size = header->size,
        };

        const struct cosmoNetworkHeader networkHeader = {
            .source = header->source,
            .dest = header->dest,
            .payload = &networkPayload,
            .size = sizeof(networkPayload),
        };

        status = cosmoNetwork_routeMessage(&networkHeader);
    }
    else
    {
        status = COSMO_MESSAGE_MALLOC_FAILED;
    }

    return status;
}

enum cosmoMessageStatus cosmoMessage_unpack(
    const struct cosmoNetworkHeader* networkHeader,
    void* unpacked
)
{
    enum cosmoMessageStatus status = COSMO_MESSAGE_STATUS_OK;

    if (NULL != networkHeader && NULL != unpacked)
    {
        const struct networkMessagePayload* networkpayload = networkHeader->payload;
        const struct cosmoMessageHeader messageHeader = {
            .source = networkHeader->source,
            .dest = networkHeader->dest,
            .msgid = networkpayload->msgId,
            .payload = networkpayload->payload,
            .size = networkpayload->size,
        };
        memcpy(unpacked, &messageHeader, sizeof(messageHeader));
    }
    else
    {
        status = COSMO_MESSAGE_STATUS_ERROR;
    }

    return status;
}
