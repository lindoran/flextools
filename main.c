#include <stdio.h>
#include <stdlib.h>

#include "floppy.h"


t_floppy floppy;

int main() {

    build_floppy(&floppy,80,DOUBLE_SIDE,DOUBLE_DENSITY);
    format(&floppy,"TEST",1);

    exit(0);
}
