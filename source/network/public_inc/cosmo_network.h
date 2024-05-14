#ifndef COSMO_MESSAGE_NETWORK_H
#define COSMO_MESSAGE_NETWORK_H

#include "cosmo_message_status.h"
#include "cosmo_message_types.h"

#include <stdbool.h>

/**
 * @brief Structure representing the header of a network message in the Cosmo Message
 * Stack.
 */
struct cosmoNetworkHeader
{
    cosmoNode source;    //!< The source node of the message.
    cosmoNode dest;      //!< The destination node of the message.
    const void* payload; //!< Payload data of the message.
    size_t size;         //!< The size of the payload data in bytes.
};

typedef enum cosmoMessageStatus (*cosmoNetworkSendCb)(const struct cosmoNetworkHeader*);

/**
 * @brief Represents a network route for sending messages.
 */
struct cosmoNetworkRoute
{
    cosmoNode dest;              //!< The destination node.
    bool remote;                 //!< Indicates if the route is for a remote node.
    cosmoNetworkSendCb callback; //!< The callback function for sending messages.
};

/**
 * @brief Structure representing the configuration of the Cosmo network.
 */
struct cosmoNetworkConfig
{
    size_t size;                           //!< Size of the network configuration.
    const struct cosmoNetworkRoute* table; //!< Pointer to the network route table.
};

/**
 * Retrieves the message route for a given network header.
 *
 * This function takes a pointer to a network header and retrieves the
 * corresponding message route.
 *
 * @param[in] header The network header of the message.
 * @param[out] route  A pointer to a `cosmoNetworkRoute` structure to store the message
 * route.
 * @return The status of the message route retrieval operation.
 */
enum cosmoMessageStatus cosmoNetwork_getMessageRoute(
    const struct cosmoNetworkHeader* header,
    struct cosmoNetworkRoute* route
);

/**
 * Routes a message in the Cosmo network.
 *
 * @param[in] header The network header of the message to be routed.
 * @return The status of the message routing operation.
 */
enum cosmoMessageStatus cosmoNetwork_routeMessage(
    const struct cosmoNetworkHeader* header
);

#endif // COSMO_MESSAGE_NETWORK_H