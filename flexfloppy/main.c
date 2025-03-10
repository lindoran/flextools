#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

#include "floppy.h"

t_floppy floppy;

int new_flag=0;
int cat_flag=0;
int extract_flag=0;
int add_flag=0;
char *infile=NULL,*outfile=NULL,*path=NULL, *filename=NULL;
char floppy_label[12];
int floppy_number=0;
int num_tracks=0,num_sectors=0;

void usage() {
    printf("Usage:\n");
    printf("flexfloppy --in <disk.dsk> --cat\n"); 
    printf("flexfloppy --in <disk.dsk> --extract <path>\n");
    printf("flexfloppy --new --tracks <num_tracks> --sectors <num_sectors> [--label <label>] [--number <number>] --out <disk.dsk>\n");
    printf("flexfloppy --in <disk.dsk> --add <filename>\n");
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

void do_new(char *filename, int tracks, int sectors, char *label, int number) {
    floppy.num_track = tracks;
    floppy.track0_sectors = sectors;
    floppy.tracks_sectors = sectors;
    floppy.side = SINGLE_SIDE; // don't care
    floppy.density = SINGLE_DENSITY; // don't care
    floppy_allocate(&floppy); 
    floppy_format(&floppy,label,number);
    floppy_export(&floppy,filename);
    floppy_release(&floppy);
    printf("OK\n");
}

void do_add(char *infile,char *filename) {
    floppy_guess_geometry(&floppy,infile); 
    floppy_import(&floppy,infile); 
    floppy_add_file(&floppy,filename);
    floppy_export(&floppy,infile);
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
            {"label", required_argument,0,'l'},
            {"number", required_argument,0,'u'},
            {"add", required_argument,0,'a'},
            {0,0,0,0}
        };

        int option_index=0;

        c = getopt_long (argc, argv, "cni:o:e:t:s:l:u:a:",
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

            case 'l':
                memset(floppy_label,'\0',11);
                strncpy(floppy_label,optarg,10);
                break;
            
            case 'u':
                floppy_number=atoi(optarg);
                break;

            case 'a':
                add_flag = 1;
                filename = optarg;
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

    // NEW
    if ( (outfile !=NULL) && (num_tracks>0) && (num_sectors>0) && new_flag ) {
        do_new(outfile,num_tracks,num_sectors,floppy_label,floppy_number);
        return 0;
    }

    // ADD
    if ( (infile != NULL) && (filename !=NULL) && add_flag) {
        do_add(infile,filename);
        return 0;
    }

    usage();
   
    return 1;
}
