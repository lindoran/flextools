#ifndef BIGENDIAN_H
#define BIGENDIAN_H

typedef struct {
    char digit[2];
} bigendian;

int bigendian_get(bigendian *b);

void bigendian_set(bigendian *b,int value);

#endif
