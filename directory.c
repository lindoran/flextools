#include "directory.h"

#include <stdio.h>

void dir_get_filename(t_dir_entry *dir,char *str) {

    for(int i=0;i<8;i ++) {
        if (dir->filename[i]==0) break;
        *str++=dir->filename[i];
    }

    *str++='.';

    for(int i=0;i<3;i ++) {
        if (dir->ext[i]==0) break;
        *str++=dir->ext[i];
    }

    *str='\0';
}

void dir_info(t_dir_entry *dir) {

    char filename[13];

    dir_get_filename(dir,filename);

    printf("Filename : %s\n",filename);
    printf("Start track/sector : %d,%d\n",dir->start_track,dir->start_sector);
    printf("End track/sector : %d,%d\n",dir->end_track,dir->end_sector);
    printf("Total sectors : %d\n",bigendian_get(&dir->total_sector));
    printf("Random file : %d\n",dir->random_file);
    printf("Creation date : %d/%d/%d\n\n",dir->creation_day,dir->creation_month,dir->creation_year);

}