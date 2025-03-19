#ifndef SECTOR_H
#define SECTOR_H

#include "bigendian.h"
#include "directory.h"

#include <stdint.h>

#define SECTOR_SIZE 256
#define VOLUME_LABEL_MAXLENGTH 10
#define SECTOR_USR_DATA_LENGTH 252

typedef struct {
    char data[256];
} t_raw_sector;

typedef struct {
    char empty[16];
    char volume_label[11];
    bigendian volume_number;
    uint8_t first_user_track;
    uint8_t first_user_sector;
    uint8_t last_user_track;
    uint8_t last_user_sector;
    bigendian total_sector;         // total free sectors
    uint8_t creation_month;
    uint8_t creation_day;
    uint8_t creation_year;
    uint8_t max_track;
    uint8_t max_sector;
    uint8_t empty2[216];
} t_sir_sector;

typedef struct {
    uint8_t next_track;
    uint8_t next_sector;
    uint8_t empty[14];
    t_dir_entry dir[DIR_ENTRY_PER_SECTOR];
} t_dir_sector;

typedef struct {
    uint8_t next_track;
    uint8_t next_sector;
    bigendian sequence;
    uint8_t data[SECTOR_USR_DATA_LENGTH];
} t_usr_sector;

typedef union {
    t_raw_sector raw;
    t_sir_sector sir;
    t_dir_sector dir;
    t_usr_sector usr;
} t_sector;


void empty_sector(t_sector *sector);
void sector_dump(t_sector *sector);
void sector_load(t_sector *sector, char *filename);

#endif
