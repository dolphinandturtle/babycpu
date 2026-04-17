#include <stdio.h>
#include <stdint.h>
#include "../include/babycpu.h"

int main(void) {
    struct Cpu cpu = cpu_new();
    uint16_t memory[256] = {
        0x0106, // Set reg0 to 6            [0x00]
        0x0507, // Set reg1 to 7            [0x01]
        0x2100, // Add reg1 to reg0         [0x02]
        0x1005, // Store reg0 to 0x05 (SUM) [0x03]
        0x6000, // Halt                     [0x04]
        0x0000  // SUM                      [0x05]
    };
    cpu_run(memory, 6, 0, &cpu);
    return 0;
}
