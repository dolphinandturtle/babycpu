#include <stdio.h>
#include <stdint.h>
#include "../include/babycpu.h"

int main(void) {
    struct Cpu cpu = cpu_new();
    uint16_t memory[256] = {
        // Set SUM and COUNT to 0
        0x0100, // Set reg0 to 0.                 [0x00]
        0x1011, // Store reg0 to 0x11 (PSUM).     [0x01]
        0x1012, // Store reg0 to 0x12 (COUNT).    [0x02]
                                                  
        // Halt if 'value at COUNT' > 9
        0x0012, // Load 0x12 (COUNT) to reg0.     [0x03]
        0x050a, // Set reg1 to 9.                 [0x04]
        0x5110, // Jump to 0x10 if reg0 > reg1.   [0x05]

        // Add 'value at COUNT' to 'value at SUM'
        0x0011, // Load 0x11 (PSUM) to reg0.      [0x06]
        0x0412, // Load 0x12 (COUNT) to reg1.     [0x07]
        0x2100, // Add reg1 to reg0               [0x08]
        0x1011, // Store reg0 to 0x11 (PSUM)      [0x09]

        // Add 1 to 'COUNT'
        0x0101, // Set reg0 to 1.                 [0x0a]
        0x2100, // Add reg1 to reg0               [0x0b]
        0x1012, // Store reg0 to 0x12 (COUNT)     [0x0c]

        // Jump back to 0x03 (comparison)
        0x0101, // Set reg0 to 1.                 [0x0d]
        0x0500, // Set reg1 to 0.                 [0x0e]
        0x5103, //                                [0x0f]

        // Halt
        0x6000, //                                [0x10]

        // Memory reserved to data
        0x0000, // PSUM                           [0x11]
        0x0000  // COUNT                          [0x12]
    };
    cpu_run(memory, 0x12+1, 0, &cpu);
    return 0;
}
