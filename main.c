#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "floppy.h"

t_floppy floppy;

int new_flag=0;
int cat_flag=0;
int extract_flag=0;
char *infile=NULL,*outfile=NULL,*path=NULL;
int num_tracks,num_sectors;

void usage() {
    printf("Usage:\n");
    printf("flexfloppy --in [disk.dsk] --cat\n"); 
    printf("flexfloppy --in [disk.dsk] --extract [path]\n");
    printf("flexfloppy --new --tracks [num_tracks] --sectors [num_sectors] --out [disk.dsk]\n");

    exit(-1);
}

void do_cat(char *filename) {
    floppy_guess_geometry(&floppy,filename);
    floppy_import(&floppy,filename);
    floppy_info(&floppy);
    floppy_cat(&floppy);
    floppy_release(&floppy);
}

void do_extract(char *filename, char *path) {
    floppy_guess_geometry(&floppy,filename);
    floppy_import(&floppy,filename);
    floppy_info(&floppy);
    floppy_extract(&floppy,path);
    floppy_release(&floppy);
}

int main(int argc, char *argv[]) {

    int c;

    while(1) {

        static struct option long_options[] = {
            {"cat", no_argument, 0, 'c'},
            {"new", no_argument, 0 ,'n'},
            {"in", required_argument,0,'i'},
            {"out", required_argument,0,'o'},
            {"extract", required_argument,0,'e'},
            {"tracks", required_argument,0,'t'},
            {"sectors", required_argument,0,'s'},
            {0,0,0,0}
        };

        int option_index=0;

        c = getopt_long (argc, argv, "cni:o:u:d:e:",
                       long_options, &option_index);

        if (c==-1) break;

        switch(c) {
            case 'c':
                cat_flag=1;
                break; 

            case 'n':
                new_flag=1;
                break;

            case 'i':
                infile=optarg;
                break;

            case 'o':
                outfile=optarg;
                break;

            case 'e':
                path=optarg;
                extract_flag=1;
                break;

            case 't':
                num_tracks=atoi(optarg);
                break;

            case 's':
                num_sectors=atoi(optarg);
                break;

            default:
                usage();
        }

    }

    // CAT
    if ( (infile!=NULL) && cat_flag) {
        do_cat(infile);
        return 0;
    }

    // EXTRACT
    if ( (infile!=NULL) && (path!=NULL) && extract_flag ) {
        do_extract(infile,path);
        return 0;
    }

    usage();
   
    return 1;
}
