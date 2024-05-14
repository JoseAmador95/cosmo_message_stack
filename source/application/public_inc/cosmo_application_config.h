/**
 * @file cosmo_application_config.h
 * @brief This file contains the public definitions, types, variables and function
 * declarations for the Cosmo Application Configuration.
 */

#ifndef COSMO_APPLICATION_CONFIG_H
#define COSMO_APPLICATION_CONFIG_H

/*****************************************************************************/
/* Public Include                                                            */
/*****************************************************************************/

#include "cosmo_application.h"

/*****************************************************************************/
/* Public Definitions                                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Public types                                                              */
/*****************************************************************************/

/*****************************************************************************/
/* Public variables                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Public function declarations                                              */
/*****************************************************************************/

/**
 * Sends a Cosmo message.
 *
 * This function sends a Cosmo message using the provided message header.
 *
 * @param header The pointer to the message header.
 * @return The status of the message sending operation.
 */
enum cosmoMessageStatus cosmoMessage_send(struct cosmoMessageHeader* header);

#endif // COSMO_APPLICATION_CONFIG_H