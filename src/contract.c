#include <stdint.h>
#include "p2p_staking.h"

// List of selectors supported by this plugin.
static const uint32_t DEPOSIT_SELECTOR = 0x2c4b04fa;
static const uint32_t WITHDRAW_SELECTOR = 0x66792ba1;

// Array of all the different selectors in the same order as the
// enum defined in the header file.
const uint32_t SELECTORS[NUM_SELECTORS] = {
    DEPOSIT_SELECTOR,
    WITHDRAW_SELECTOR,
};
