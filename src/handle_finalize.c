#include "p2p_staking.h"

void handle_finalize(ethPluginFinalize_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;

    msg->uiType = ETH_UI_TYPE_GENERIC;

    msg->result = ETH_PLUGIN_RESULT_OK;

    switch (context->selectorIndex) {
        case DO_DEPOSIT:
            msg->numScreens = 1;
            break;
        case DO_WITHDRAW:
            msg->numScreens = 0;
            break;

        default:
            PRINTF("Selector index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }
}
