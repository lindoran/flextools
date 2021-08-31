#include <stdlib.h>
#include <string.h>

#include "sector.h"



void empty_sector(t_sector *sector) {
    memset(sector,0,SECTOR_SIZE);
}
