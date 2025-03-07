#ifndef BIGENDIAN_H
#define BIGENDIAN_H

#include <stdint.h>

typedef struct {
    uint8_t digit[2];
} bigendian;

unsigned int bigendian_get(bigendian *b);

void bigendian_set(bigendian *b,unsigned int value);

#endif
