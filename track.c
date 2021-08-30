#include <stdlib.h>

#include "track.h"

void track_init_sectors(t_track *track,int num_sector) {
    track->num_sector = num_sector;
    
    track->sectors = (t_sector *)malloc(num_sector * sizeof(num_sector) );
    if (track->sectors == NULL) {
        exit(EXIT_FAILURE);
    }
}
