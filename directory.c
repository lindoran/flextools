#include "directory.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

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

int dir_set_filename(t_dir_entry *dir, char *str) {
    
    // get rid of path
    char *begin = strrchr(str,'/');
    if (begin==NULL) 
        begin=str;
    else
        begin++;

    // find DOT
    char *dot = strchr(begin,'.');
    if (dot==NULL) return 0;

    // filename should be max. 8 characters
    if ((dot-begin-1)>8) return 0;

    // extension should be max. 3 characters
    if ((strlen(dot)-1)>3) return 0;

    // clear entries content
    memset(dir->filename,'\0',8);
    memset(dir->ext,'\0',3);

    // set entries
    *dot='\0';
    strcpy(dir->filename,begin);
    strcpy(dir->ext,++dot); // an extra '\0' is written at the end on an empty field which is already zeroed.

    return 1;
}

void dir_set_current_date(t_dir_entry *dir) {
    
    // get current date
    time_t timestamp = time(NULL);
    struct tm *timeinfo = localtime(&timestamp);

    dir->creation_day = timeinfo->tm_mday;
    dir->creation_month = timeinfo->tm_mon+1;
    dir->creation_year = timeinfo->tm_year % 100;
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