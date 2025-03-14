#ifndef BINDATA_H
#define BINDATA_H

#include <stdint.h>

#define DATA_CHUNK_SIZE 1024

typedef struct s_data_chunk {
    uint16_t start_addr;
    int data_size;
    int data_alloc_size;
    uint8_t *data;
    struct s_data_chunk *next_data_chunk;
} t_data_chunk ; 

typedef struct {
    uint16_t run_addr;
    int has_run_addr;
    int data_chunk_count;
    t_data_chunk *data_chunk; // linked list of data chunks
} t_data ;

void init_data(t_data *data);
void free_data(t_data *data);

t_data_chunk *data_new_chunk(t_data *data,uint16_t start_addr);

void add_data(t_data_chunk *df,uint8_t value);

#endif