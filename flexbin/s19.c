#include "s19.h"

#include <stdio.h>
#include <stdlib.h>

void s19_load(uint8_t *memory, uint16_t *start_address, char *filename) {

    FILE *fp;

    fp = fopen(filename,"rb");
    if (fp==NULL) {
        fprintf(stderr,"Cannot read %s\n",filename);
        exit(-1);
    }

    int s_type;
    unsigned int s_byte_count;
    unsigned int s_address;
    unsigned int s_data;
    unsigned int s_checksum;
    unsigned int calc_checksum;

    int line=0;

    while(!feof(fp)) {

        line ++;

        calc_checksum=0;

        fscanf(fp,"S%1d%02X%04X",
            &s_type,
            &s_byte_count,
            &s_address);

        // init checksum
        calc_checksum=s_byte_count + (s_address&0xff) + (s_address>>8);

        switch(s_type) {

            case 1:
                // we have s_byte_count - 3 bytes of data, then 1 checksum byte 
                for(unsigned int i=0;i<s_byte_count-3;i ++) {
                    fscanf(fp,"%02X",&s_data);
                    *(memory + s_address++)=(uint8_t)s_data;
                    calc_checksum+=s_data;
                }

                break;

            case 9:
                // we have 1 checksum byte

                // save the start_address
                *start_address = (uint16_t)s_address;
                break;
            default:
                fprintf(stderr,"Unknown record type %d\n",s_type);
                exit(-1);
        }

        // read checksum
        fscanf(fp,"%02X\n", &s_checksum);

        // calculate the checksum
        calc_checksum = 0xFF - (calc_checksum&0xFF);

        if (calc_checksum != s_checksum ) {
            fprintf(stderr,"checksum error line %d (%02X instead of %02X)\n",
                line, calc_checksum, s_checksum);
                exit(-1);
        }
    
    }

    fclose(fp);
}   