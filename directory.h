#ifndef DIRECTORY_H
#define DIRECTORY_H
   
#include "bigendian.h"

#include <stdint.h>

#define DIR_ENTRY_PER_SECTOR 10

typedef struct {
    char filename[8];
    char ext[3];
    uint8_t empty[2];
    uint8_t start_track;
    uint8_t start_sector;
    uint8_t end_track;
    uint8_t end_sector;
    bigendian total_sector;
    uint8_t random_file;
    uint8_t empty2;
    uint8_t creation_month;
    uint8_t creation_day;
    uint8_t creation_year;
} t_dir_entry;


void dir_get_filename(t_dir_entry *dir,char *str);
void dir_get_filename_pretty(t_dir_entry *dir,char *str);

void dir_info(t_dir_entry *dir);

#endif
