
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "lily58.h"

#define L_BASE 0
#define L_GAMING 1
#define L_FN 2

char layer_state_str[24];

const char *read_layer_state(void) {
    if ((layer_state >> L_FN) & 1)
    {
        snprintf(layer_state_str, sizeof(layer_state_str), "FN");
    }
    else if ((layer_state >> L_GAMING) & 1)
    {
        snprintf(layer_state_str, sizeof(layer_state_str), "Gaming");
    }
    else
    {
        snprintf(layer_state_str, sizeof(layer_state_str), "Base");
    }
    return layer_state_str;
}
