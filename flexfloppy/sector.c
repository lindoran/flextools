#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "sector.h"



void empty_sector(t_sector *sector) {
    memset(sector,0,SECTOR_SIZE);
}

void sector_dump(t_sector *sector) {


    printf("   ");
    for(int i=0;i<16;i++) printf("  %X",i);
    printf("\n");

    for(int i=0;i<16;i++) {
        printf("%X0 ",i);
        for(int j=0;j<16;j ++) printf(" %2X",sector->raw.data[i*16+j]);
        printf(" ");
        for(int j=0;j<16;j ++) {
            unsigned char c=sector->raw.data[i*16+j];
            if (c<32 || c>127) printf("."); else printf("%c",sector->raw.data[i*16+j]);
        }
        printf("\n");
    }

}
