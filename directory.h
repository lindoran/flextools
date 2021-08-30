#ifndef DIRECTORY_H
#define DIRECTORY_H
   
#include "bigendian.h"

typedef struct {
    char filename[8];
    unsigned char start_track;
    unsigned char start_sector;
    unsigned char end_track;
    unsigned char end_sector;
    bigendian total_sector;
    char random_file;
    unsigned char creation_month;
    unsigned char creation_day;
    unsigned char creation_year;
} t_dir_entry;

#endif
