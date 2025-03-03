#ifndef DIRECTORY_H
#define DIRECTORY_H
   
#include "bigendian.h"

#define DIR_ENTRY_PER_SECTOR 10

typedef struct {
    char filename[8];
    char ext[3];
    char empty[2];
    unsigned char start_track;
    unsigned char start_sector;
    unsigned char end_track;
    unsigned char end_sector;
    bigendian total_sector;
    char random_file;
    char empty2;
    unsigned char creation_month;
    unsigned char creation_day;
    unsigned char creation_year;
} t_dir_entry;

void dir_get_filename(t_dir_entry *dir,char *str);

void dir_info(t_dir_entry *dir);

#endif
