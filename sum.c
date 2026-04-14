#include <stdio.h>
#include <stdint.h>
#include "babycpu.h"

int main(void) {
    // CPU
    struct Cpu cpu = cpu_new();

    // Insert instructions sequentially following the format:
    //      OP   R0 R1 ADDR
    // 0000 0000 00 00 0000
    uint16_t memory[16] = {
        0x0005, // 0
        0x0046, // 1
        0x0300, // 2
        0x0107, // 3
        0x00ff, // 4
        0x00f0, // 5
        0x0003, // 6
        0x0000, // 7
        0x0000, // 8
        0x0000, // 9
        0x0000, // a
        0x0000, // b
        0x0000, // c
        0x0000, // d
        0x0000, // e
        0x0000  // f
    };

    cpu_run(memory, 0, &cpu);
    printf("counter: %d\n", cpu.counter);
    printf("signal: %d\n", cpu.signal);
    // printf("result: %d\n", memory[7]);
    return 0;
}
