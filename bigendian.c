#include <stdio.h>
#include <stdlib.h>

#include "bigendian.h"

unsigned int bigendian_get(bigendian *b) {
    return b->digit[0]*256+b->digit[1];
}

void bigendian_set(bigendian *b,unsigned int value) {
    if (value>65535) {
        perror("bigendian too big");
        exit(EXIT_FAILURE);
    }

    b->digit[0]=value/256;
    b->digit[1]=value%256;
}
