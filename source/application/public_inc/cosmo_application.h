/**
 * @file cosmo_application.h
 * @brief This file contains the public definitions, types, variables, and function
 * declarations for the Cosmo Application.
 */

#ifndef COSMO_APPLICATION_H
#define COSMO_APPLICATION_H

#include "cosmo_message_status.h"
#include "cosmo_message_types.h"

#include <stddef.h>
#include <stdint.h>

/**
 * @brief This structure represents a Cosmo message header.
 */
struct cosmoMessageHeader
{
    cosmoMsgId msgId;      //!< The ID of the message.
    cosmoNode source;      //!< The source node of the message.
    cosmoNode dest;        //!< The destination node of the message.
    const void* payload;   //!< A pointer to the payload data.
    cosmoPayloadSize size; //!< The size of the payload data.
};

/**
 * @brief Allocates a Cosmo message with the specified parameters.
 *
 * This function allocates a Cosmo message with the specified parameters. It creates a
 * message header structure and initializes it with the provided message ID, source
 * node, destination node, payload, and payload size. The allocated message header is
 * returned through the 'header' parameter.
 *
 * @param[out] header The pointer to the message header structure.
 * @param[in] msgId The ID of the message.
 * @param[in] source The source node of the message.
 * @param[in] dest The destination node of the message.
 * @param[in] payload The pointer to the message payload.
 * @param[in] size The size of the message payload.
 * @return The status of the message allocation. Possible values are:
 *         - COSMO_MESSAGE_SUCCESS: The message allocation was successful.
 *         - COSMO_MESSAGE_INVALID_ARGUMENT: One or more of the input arguments is
 *                                           invalid.
 *         - COSMO_MESSAGE_MEMORY_ERROR: There was an error allocating memory for the
 *                                       message header.
 */
enum cosmoMessageStatus cosmoMessage_allocate(
    struct cosmoMessageHeader* header,
    cosmoMsgId msgId,
    cosmoNode source,
    cosmoNode dest,
    const void* payload,
    size_t size
);

/**
 * @brief Allocates and sends a Cosmo message.
 *
 * This function allocates a Cosmo message, sets the source and destination nodes,
 * copies the payload data, and sends the message to the destination node.
 *
 * @param[in] msgId The ID of the message to be sent.
 * @param[in] source The source node of the message.
 * @param[in] dest The destination node of the message.
 * @param[in] payload A pointer to the payload data.
 * @param[in] size The size of the payload data in bytes.
 * @return The status of the message allocation and sending operation.
 * @note The function assumes that the payload data is valid and the size is correct.
 */
enum cosmoMessageStatus cosmoMessage_allocateAndSend(
    cosmoMsgId msgId,
    cosmoNode source,
    cosmoNode dest,
    const void* payload,
    size_t size
);

#endif // COSMO_APPLICATION_H