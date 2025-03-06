#include <stdio.h>
#include <stdlib.h>

#include "floppy.h"


t_floppy floppy;

int main(int argc, char *argv[]) {

    if (argc!=2) {
        printf("Usage: flexfloppy [disk.dsk]\n");
        return -1;
    }

    char *filename = argv[1];

    floppy_guess_geometry(&floppy,filename);
    //floppy_build(&floppy,80,DOUBLE_SIDE,DOUBLE_DENSITY);
    //floppy_build(&floppy,80,DOUBLE_SIDE,SINGLE_DENSITY);
    //floppy_format(&floppy,"TEST",1);
    //floppy_export(&floppy,"test.dsk");

    floppy_import(&floppy,filename);


    floppy_info(&floppy);
    floppy_cat(&floppy);
   // floppy_extract(&floppy,"out");
     printf("OK\n");
    floppy_release(&floppy);

    exit(0);
}
