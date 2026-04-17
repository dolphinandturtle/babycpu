#include "include/babycpu.h"

int main(void) {
    struct Cpu cpu = cpu_new();
    uint16_t memory[16] = {
        0x0000,
        0x0000,
        0x0000,
        0x0000,
        0x0000,
        0x0000,
        0x0000,
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
    cpu_run(memory, 16, 0, &cpu);
    return 0;
}
