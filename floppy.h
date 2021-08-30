#ifndef FLOPPY_H
#define FLOPPY_H

#include "track.h"

#define TRACK0_SECTORS 10
#define SD_SECTORS 10
#define DD_SECTORS 18

enum e_side { SINGLE_SIDE=1,DOUBLE_SIDE };
enum e_density {SINGLE_DENSITY=1,DOUBLE_DENSITY };

typedef struct {
    int num_track;
    enum e_side side;
    enum e_density density;
    t_track *tracks;
} t_floppy;


void build_floppy(t_floppy *floppy,int num_tracks,enum e_side side,enum e_density density);

void format(t_floppy *floppy,char *name,int number);

#endif
