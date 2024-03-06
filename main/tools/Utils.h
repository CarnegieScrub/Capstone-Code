// UTIL.h
#ifndef UTIL_H
#define UTIL_H
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

// this file is completely wrong and will probably be wiped and completely re-
// written

typedef enum {
    PERIPHERAL_BT,
    PERIPHERAL_CELL,
    // Other peripherals can be defined here
} PeripheralType;

void util_setup_peripheral(PeripheralType type);
bool util_check_connection();
void util_reconnect();
char* util_serialize_data(void* data, size_t dataSize);
void util_confirm_response();
#endif
