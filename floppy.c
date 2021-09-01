#include <stdlib.h>
#include <stdio.h>

// for stat
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "floppy.h"
#include "track.h"
#include "sector.h"
#include "bigendian.h"

// private functions
int num_sector_for_track(t_floppy *floppy,int t);
int get_floppy_size(t_floppy *floppy);


void floppy_build(t_floppy *floppy,int num_track,enum e_side side,enum e_density density) {

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


void floppy_release(t_floppy *floppy) {

    t_track *track=floppy->tracks;
    for (int t=0;t<floppy->num_track;t ++) {
        free(track->sectors);
        track++;
    }

    free(floppy->tracks);
}

void floppy_format(t_floppy *floppy,char *label,int number) {

    t_track *track;
    t_sector *sector;
    
    // track 0 = system data
    track = floppy->tracks;
    sector = track->sectors;

    // track 0 / sector 1 = boot sector
    empty_sector(sector++);

    // track 0 / sector 2 = boot sector (2)
    empty_sector(sector++);
    
    // track 0 / sector 3 = System Information Record
    empty_sector(sector);

    for(int i=0;i<VOLUME_LABEL_MAXLENGTH;i++) {
        if (label[i]==0) break;
        sector->sir.volume_label[i] = label[i];
    }

    bigendian_set(&sector->sir.volume_number,number);
    sector->sir.first_user_track=1;
    sector->sir.first_user_sector=1;
    sector->sir.last_user_track=floppy->num_track-1;
    sector->sir.last_user_sector=num_sector_for_track(floppy,1);
    bigendian_set(&sector->sir.total_sector,0); 
    /*unsigned char creation_month;
    unsigned char creation_day;
    unsigned char creation_year;*/
    sector->sir.max_track = sector->sir.last_user_track;
    sector->sir.max_sector = sector->sir.last_user_sector;

    

    sector++;

    // track 0 / sector 4 = empty
    empty_sector(sector++);
    

    // track 0 / sector 5... = directory
    for (int s=4;s<num_sector_for_track(floppy,0);s++) {
        unsigned char next_sector=s+2;
        if ( s==(num_sector_for_track(floppy,0)-1) ) { next_sector=0; }
        empty_sector(sector);
        sector->dir.next_sector = next_sector; 
        sector++;
    }

    // track 1... = user data
    for (int t=1;t<floppy->num_track;t ++) {
        track++;
        for(int s=0;s<num_sector_for_track(floppy,t);s ++) {

            t_sector *sector = &track->sectors[s];

            unsigned char next_track=t;
            unsigned char next_sector=s+2;

            if (s==(num_sector_for_track(floppy,t)-1)) {
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

        return num_sector*floppy->side;
}

void floppy_export(t_floppy *floppy,char *filename) {

    FILE *fp = fopen(filename,"wb");
    if (fp == NULL) {
        perror("cannot open file");
        exit(EXIT_FAILURE);
    }

    for (int t=0;t<floppy->num_track;t ++) {
        t_track *track = &floppy->tracks[t];
        fwrite(track->sectors,SECTOR_SIZE,track->num_sector,fp);
    }

    fclose(fp);

}

void floppy_import(t_floppy *floppy,char *filename) {
   
    struct stat sb;

    if (stat(filename,&sb)==-1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    int filesize = sb.st_size;

    if (filesize != get_floppy_size(floppy)) {
        perror("bad size");
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(filename,"rb");
    if (fp == NULL) {
        perror("cannot open file");
        exit(EXIT_FAILURE);
    }

    for (int t=0;t<floppy->num_track;t ++) {
        t_track *track = &floppy->tracks[t];
        fread(track->sectors,SECTOR_SIZE,track->num_sector,fp);
    }

    fclose(fp);


}

int get_floppy_size(t_floppy *floppy) {

    int size = num_sector_for_track(floppy,0) + num_sector_for_track(floppy,1)*(floppy->num_track-1);

    return size*SECTOR_SIZE;
}

void floppy_info(t_floppy *floppy) {

    t_sector *sector = &floppy->tracks->sectors[2];

    printf("Volume label  : %s\n",sector->sir.volume_label);
    printf("Volume number : %d\n",bigendian_get(&sector->sir.volume_number));
    printf("Creation date : %d/%d/%d\n",sector->sir.creation_day,sector->sir.creation_month,sector->sir.creation_year);
    printf("Tracks        : %d\n",floppy->num_track);
    printf("Total sectors : %d\n",bigendian_get(&sector->sir.total_sector));
    printf("Max track     : %d\n",sector->sir.max_track);
    printf("Max sector    : %d\n",sector->sir.max_sector);

}

void floppy_cat(t_floppy *floppy) {

    char filename[13];

    t_sector *sector = &floppy->tracks->sectors[4];

    while (sector->dir.next_sector) {

        for(int i=0;i<DIR_ENTRY_PER_SECTOR;i ++) {
            t_dir_entry *dir = &sector->dir.dir[i];

            if (dir->filename[0]==0) break;

            dir_get_filename(dir,filename);

            printf("%s\t%d\t%d/%d/%d\n",
                    filename,
                    bigendian_get(&dir->total_sector),
                    dir->creation_day, dir->creation_month,dir->creation_year
                    );

        }

        sector = &floppy->tracks->sectors[sector->dir.next_sector - 1] ;
    }

}
