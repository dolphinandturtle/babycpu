#include <stdio.h>
#include <stdint.h>
#include "../include/babycpu.h"

int main(void) {
    struct Cpu cpu = cpu_new();
    uint16_t memory[16] = {
        0x0005,
        0x0046,
        0x0300,
        0x0107,
        0x00ff,
        0x00f0,
        0x0003,
        0x0000,
        0x0000,
        0x0000,
        0x0000,
        0x0000,
        0x0000,
        0x0000,
        0x0000,
        0x0000
    };
    cpu_run(memory, 0, &cpu);
    return 0;
}
