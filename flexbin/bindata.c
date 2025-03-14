#include "bindata.h"

#include <stdio.h>
#include <stdlib.h>

void init_data(t_data *data) {
    data->run_addr=0;
    data->has_run_addr=0;
    data->data_chunk_count=0;
    data->data_chunk = NULL;
}

void free_data(t_data *data) {
    
    t_data_chunk *chunk = data->data_chunk;

    while(chunk) {
        free(chunk->data);
        t_data_chunk *next_chunk = chunk->next_data_chunk;
        free(chunk);
        chunk=next_chunk;
    }
    
    data->data_chunk = NULL;

}

t_data_chunk *data_new_chunk(t_data *data,uint16_t start_addr) {

    t_data_chunk *current_chunk = data->data_chunk;

    // point to last chunk
    while(current_chunk && current_chunk->next_data_chunk ) {
        current_chunk = current_chunk->next_data_chunk;
    }

    // allocate a new chunk
    t_data_chunk *chunk = malloc(sizeof(t_data_chunk));
    data->data_chunk_count++;

    chunk->start_addr=start_addr;
    chunk->data_size=0;
    chunk->data_alloc_size=DATA_CHUNK_SIZE;
    chunk->data=malloc(DATA_CHUNK_SIZE);
    chunk->next_data_chunk = NULL;

    // link the new chunk
    if (current_chunk)
        current_chunk->next_data_chunk = chunk;
    else
        data->data_chunk = chunk;
    
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