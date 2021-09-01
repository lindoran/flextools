#ifndef SECTOR_H
#define SECTOR_H

#include "bigendian.h"
#include "directory.h"

#define SECTOR_SIZE 256
#define VOLUME_LABEL_MAXLENGTH 10

typedef struct {
    char data[256];
} t_raw_sector;

typedef struct {
    char empty[16];
    char volume_label[11];
    bigendian volume_number;
    unsigned char first_user_track;
    unsigned char first_user_sector;
    unsigned char last_user_track;
    unsigned char last_user_sector;
    bigendian total_sector;
    unsigned char creation_month;
    unsigned char creation_day;
    unsigned char creation_year;
    unsigned char max_track;
    unsigned char max_sector;
    char empty2[216];
} t_sir_sector;

typedef struct {
    unsigned char next_track;
    unsigned char next_sector;
    char empty[14];
    t_dir_entry dir[DIR_ENTRY_PER_SECTOR];
} t_dir_sector;

typedef struct {
    unsigned char next_track;
    unsigned char next_sector;
    bigendian sequence;
    char data[252];
} t_usr_sector;

typedef union {
    t_raw_sector raw;
    t_sir_sector sir;
    t_dir_sector dir;
    t_usr_sector usr;
} t_sector;


void empty_sector(t_sector *sector);
void sector_dump(t_sector *sector);

#endif
