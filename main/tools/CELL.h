// CELL.h
#ifndef CELL_H
#define CELL_H
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

void initCELL();

void sendCELLData(const char* data);

bool checkCELLResponse();

#endif