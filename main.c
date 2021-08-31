#include <stdio.h>
#include <stdlib.h>

#include "floppy.h"


t_floppy floppy;

int main() {

    floppy_build(&floppy,80,DOUBLE_SIDE,DOUBLE_DENSITY);
    //floppy_build(&floppy,40,SINGLE_SIDE,SINGLE_DENSITY);
    floppy_format(&floppy,"TEST",1);
    floppy_export(&floppy,"test.dsk");

    exit(0);
}
