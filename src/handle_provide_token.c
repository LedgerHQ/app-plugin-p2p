#include "p2p_staking.h"

void handle_provide_token(void *parameters) {
    ethPluginProvideInfo_t *msg = (ethPluginProvideInfo_t *) parameters;

    msg->result = ETH_PLUGIN_RESULT_OK;
}
