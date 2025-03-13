#include "bindata.h"

#include <stdio.h>
#include <stdlib.h>

void init_data(t_data *data) {
    data->run_addr=0;
    data->has_run_addr=0;
    data->data_chunk_count=0;
}

void free_data(t_data *data) {
    
    for(int i=0;i<data->data_chunk_count;i ++) {
        t_data_chunk *chunk=&data->data_chunk[i];
        free(chunk->data);
    }

}

t_data_chunk *data_new_chunk(t_data *data,uint16_t start_addr) {
    data->data_chunk_count++;
    if (data->data_chunk_count>=MAX_DATA_CHUNK) {
        fprintf(stderr,"Too many data chunks\n");
        exit(-1);
    }

    t_data_chunk *chunk = &data->data_chunk[ data->data_chunk_count-1];

    chunk->start_addr=start_addr;
    chunk->data_size=0;
    chunk->data_alloc_size=DATA_CHUNK_SIZE;
    chunk->data=malloc(DATA_CHUNK_SIZE);
    
    return chunk;   
}

void add_data(t_data_chunk *chunk,uint8_t value) {

    // resize data chunk if needed
    if (chunk->data_size>=chunk->data_alloc_size) {
        chunk->data_alloc_size *=2;
        chunk->data=realloc(chunk->data,chunk->data_alloc_size);
    }

    *(chunk->data+chunk->data_size++) = value;
}