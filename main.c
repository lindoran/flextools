#include <stdio.h>
#include <stdlib.h>

#include "floppy.h"


t_floppy floppy;

void usage() {
    printf("Usage: flexfloppy [disk.dsk]\n");
    exit(-1);
}

void do_cat(char *filename) {
    floppy_guess_geometry(&floppy,filename);
    floppy_import(&floppy,filename);
    floppy_info(&floppy);
    floppy_cat(&floppy);
    floppy_release(&floppy);
}

int main(int argc, char *argv[]) {

    if (argc<2) {
        usage();
    }

    char *filename = argv[1];

    if (argc==2) {
        do_cat(filename);
        exit(0);
    }

    usage();

    return 0;
}
