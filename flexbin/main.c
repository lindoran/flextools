#include <stdio.h>
#include <stdint.h>

#include "bindata.h"
#include "s19_file.h"

t_data data;

int main(int argc, char *argv[]) {

    init_data(&data);

    s19_load(&data,"newdisk.s19");


    free_data(&data);

    return 0;
}