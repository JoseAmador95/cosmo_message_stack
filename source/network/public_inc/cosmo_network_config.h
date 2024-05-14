#ifndef COSMO_MESSAGE_NETWORK_CONFIG_H
#define COSMO_MESSAGE_NETWORK_CONFIG_H

#include "cosmo_network.h"

const struct cosmoNetworkConfig cosmoNetwork_getConfig(void);
bool cosmoNetwork_sendLocal(const struct cosmoNetworkHeader* header);

#endif // COSMO_MESSAGE_NETWORK_CONFIG_H