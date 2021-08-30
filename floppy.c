#include <stdlib.h>

#include "floppy.h"
#include "track.h"

// private functions
int num_sector_for_track(t_floppy *floppy,int t);


void build_floppy(t_floppy *floppy,int num_track,enum e_side side,enum e_density density) {

    floppy->num_track = num_track;
    floppy->side = side;
    floppy->density = density;

    floppy->tracks = (t_track *)malloc(num_track * sizeof(t_track));
    if (floppy->tracks == NULL) {
        exit(EXIT_FAILURE);
    }

    for(int t=0;t<num_track;t++) {
        track_init_sectors(&floppy->tracks[t],num_sector_for_track(floppy,t));
    }

}

void format(t_floppy *floppy,char *name,int number) {

    t_track *track;
    
    // track 0 = system data
    track = floppy->tracks;

    // track 0 / sector 1 = boot sector
    // track 0 / sector 2 = boot sector (2)
    // track 0 / sector 3 = System Information Record
    // track 0 / sector 4 = empty
    // track 0 / sector 5 - 10 = directory

    // track 1-n = user data
    for (int t=1;t<floppy->num_track;t ++) {
        for(int s=1;s<=num_sector_for_track(floppy,t);s ++) {
            t_sector *sector = &track->sectors[s];

            unsigned char next_track=t;
            unsigned char next_sector=s+1;

            if (s==num_sector_for_track(floppy,t)) {
                next_track++;
                next_sector=1;
                if (t==(floppy->num_track-1)) {
                    next_track=0;
                    next_sector=0;
                }
            }


            sector->usr.next_track = next_track;
            sector->usr.next_sector = next_sector; 
        }        
    }



    
}

int num_sector_for_track(t_floppy *floppy,int t) {

        int num_sector = floppy->density==SINGLE_DENSITY?SD_SECTORS:DD_SECTORS;
        if (t==0) num_sector = TRACK0_SECTORS;

        return num_sector;
}
