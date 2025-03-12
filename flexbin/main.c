#include <stdio.h>
#include <stdint.h>

#include "s19.h"

uint8_t memory[65536];
uint16_t start_address;

int main(int argc, char *argv[]) {

    s19_load(memory,&start_address,"bootsector.s19");

    return 0;
}