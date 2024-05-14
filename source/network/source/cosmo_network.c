#include "cosmo_network.h"

#include "cosmo_message_status.h"
#include "cosmo_message_types.h"
#include "cosmo_network_config.h"

#include <stdbool.h>

enum cosmoMessageStatus cosmoNetwork_getMessageRoute(
    const struct cosmoNetworkHeader* header,
    struct cosmoNetworkRoute* route
)
{
    enum cosmoMessageStatus status = COSMO_MESSAGE_STATUS_OK;

    if (NULL != header && NULL != route)
    {
        const struct cosmoNetworkConfig config = cosmoNetwork_getConfig();
        bool found = false;

        for (size_t i = 0U; !found && i < config.size; i++)
        {
            const struct cosmoNetworkRoute iterRoute = config.table[i];
            if (header->dest == iterRoute.dest)
            {
                found = true;
                *route = iterRoute;
            }
        }

        if (!found)
        {
            status = COSMO_MESSAGE_STATUS_ERROR;
        }
    }
    else
    {
        status = COSMO_MESSAGE_STATUS_ERROR;
    }

    return status;
}

enum cosmoMessageStatus cosmoNetwork_routeMessage(
    const struct cosmoNetworkHeader* header
)
{
    enum cosmoMessageStatus status = COSMO_MESSAGE_STATUS_OK;

    if (NULL != header)
    {
        struct cosmoNetworkRoute route = {
            .dest = COSMO_NODE_MAX,
            .remote = false,
            .callback = NULL,
        };

        status = cosmoNetwork_getMessageRoute(header, &route);

        if (status == COSMO_MESSAGE_STATUS_OK)
        {
            if (route.remote && route.callback != NULL)
            {
                route.callback(header);
            }
            else if (!route.remote)
            {
                const bool sent = cosmoNetwork_sendLocal(header);
                status = (sent) ? status : COSMO_MESSAGE_STATUS_ERROR;
            }
            else
            {
                // Do nothing
            }
        }
    }
    else
    {
        status = COSMO_MESSAGE_STATUS_ERROR;
    }

    return status;
}