#include "directory.h"

#include <stdio.h>
#include <string.h>

void dir_get_filename(t_dir_entry *dir,char *str) {

    memset(str,0,13);

    strncpy(str,dir->filename,8);
    strcat(str,".");
    strncat(str,dir->ext,3);

}

void dir_get_filename_pretty(t_dir_entry *dir,char *str) {

    memset(str,' ',13);
    *(str+13)='\0';

    memcpy(str,dir->filename,8);
    for(int i=0;i<8;i++) 
        if ( *(str+i) == '\0' ) *(str+i)=' ';
    strncpy(str+9,dir->ext,3);

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