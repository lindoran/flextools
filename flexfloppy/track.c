#include <stdlib.h>

#include "track.h"
#include "sector.h"

void track_init_sectors(t_track *track,int num_sector) {
    track->num_sector = num_sector;
    track->sectors = (t_sector *)malloc(num_sector * SECTOR_SIZE );
    if (track->sectors == NULL) {
        exit(EXIT_FAILURE);
    }
}
