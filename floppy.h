#ifndef FLOPPY_H
#define FLOPPY_H

#include "track.h"

#include <string.h>

#define TRACK0_SECTORS 10
#define SD_SECTORS 10
#define DD_SECTORS 18

enum e_side { SINGLE_SIDE=1,DOUBLE_SIDE };
enum e_density {SINGLE_DENSITY=1,DOUBLE_DENSITY };

typedef struct {
    int num_track;
    enum e_side side;
    enum e_density density;
    int track0_sectors;
    int tracks_sectors;
    t_track *tracks;
} t_floppy;


void floppy_allocate(t_floppy *floppy);
void floppy_release(t_floppy *floppy);

void floppy_build(t_floppy *floppy,int num_tracks,enum e_side side,enum e_density density);

void floppy_format(t_floppy *floppy,char *label,int number);

int floppy_guess_geometry(t_floppy *floppy,char *filename);
void floppy_export(t_floppy *floppy,char *filename);
void floppy_import(t_floppy *floppy,char *filename);

void floppy_info(t_floppy *floppy);
void floppy_cat(t_floppy *floppy);

void floppy_extract(t_floppy *floppy, char *outdir);

#endif
