#include <stdbool.h>
#include "p2p_staking.h"

static bool handle_deposit_ui_preview(ethQueryContractUI_t *msg, context_t *context) {
    (void) context;
    strlcpy(msg->title, "Stake", msg->titleLength);

    const uint8_t *eth_amount = msg->pluginSharedRO->txContent->value.value;
    uint8_t eth_amount_size = msg->pluginSharedRO->txContent->value.length;

    return amountToString(eth_amount,
                          eth_amount_size,
                          WEI_TO_ETHER,
                          "ETH",
                          msg->msg,
                          msg->msgLength);
}

static bool handle_deposit_ui(ethQueryContractUI_t *msg, context_t *context) {
    bool ret = false;

    switch (msg->screenIndex) {
        case 0:
            ret = handle_deposit_ui_preview(msg, context);
            break;

        default:
            PRINTF("Received a screen index out of bounds: %d", msg->screenIndex);
            break;
    }
    return ret;
}

static bool handle_withdraw_ui_preview(ethQueryContractUI_t *msg, context_t *context) {
    (void) context;
    strlcpy(msg->title, "Unstake", msg->titleLength);
    strlcpy(msg->msg, "ETH", msg->msgLength);
    return true;
}

static bool handle_withdraw_ui(ethQueryContractUI_t *msg, context_t *context) {
    bool ret = false;

    switch (msg->screenIndex) {
        case 0:
            ret = handle_withdraw_ui_preview(msg, context);
            break;

        default:
            PRINTF("Received a screen index out of bounds: %d", msg->screenIndex);
            break;
    }
    return ret;
}

void handle_query_contract_ui(ethQueryContractUI_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;
    bool ret = false;

    // msg->title is the upper line displayed on the device.
    // msg->msg is the lower line displayed on the device.

    // Clean the display fields.
    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    switch (context->selectorIndex) {
        case DO_DEPOSIT:
            ret = handle_deposit_ui(msg, context);
            break;
        case DO_WITHDRAW:
            ret = handle_withdraw_ui(msg, context);
            break;
        // Keep this
        default:
            PRINTF("Received an invalid screenIndex\n");
            break;
    }
    msg->result = ret ? ETH_PLUGIN_RESULT_OK : ETH_PLUGIN_RESULT_ERROR;
}
