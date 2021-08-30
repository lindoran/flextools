#ifndef TRACK_H
#define TRACK_H

#include "sector.h"

typedef struct {
    int num_sector;
    t_sector *sectors;
} t_track;


void track_init_sectors(t_track *track,int num_sector);

#endif
