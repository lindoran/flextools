#include "cmd_file.h"

#include <stdio.h>
#include <stdlib.h>

// 02 + 2 bytes addr + 1 byte count (max C4) + data
// 16 + 2 bytes run addr
// final size multiple of 252

void cmd_save(t_data *data, char *filename) {

    FILE *fp;

    fp = fopen(filename,"wb");
    if (fp==NULL) {
        fprintf(stderr,"Cannot create %s\n",filename);
        exit(-1);
    }

    t_data_chunk *chunk=data->data_chunk;

    while(chunk) {
        unsigned int start_addr = chunk->start_addr;
        unsigned int end_addr = start_addr + chunk->data_size;

        while(start_addr<end_addr) {
            
            fputc(2,fp);
            fputc(start_addr>>8,fp);
            fputc(start_addr&0xFF,fp);

            int length = end_addr - start_addr + 1;
            if (length>255) length=255;

            fputc(length,fp);

            for(int i=0;i<length;i++) {
                fputc(*(chunk->data+i),fp);
                start_addr ++;
            }

        }
        
        chunk = chunk->next_data_chunk;
    }

    // run address
    if (data->has_run_addr) {
        fputc(16,fp);
        fputc(data->run_addr>8,fp);
        fputc(data->run_addr&0xFF,fp);
    }
    


    fclose(fp);
}