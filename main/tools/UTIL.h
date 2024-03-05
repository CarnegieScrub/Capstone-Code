// UTIL.h
#ifndef UTIL_H
#define UTIL_H
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

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
