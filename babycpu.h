#include <stdint.h>

struct Cpu {
    uint16_t instruction;
    uint8_t counter;
    uint8_t registers[4];
    uint8_t signal;
};

enum Op {
    LOAD = 0x00,
    STORE = 0x01,
    INCREMENT = 0x02,
    ADD = 0x03,
    SUB = 0x04,
    JUMP = 0x05,
    JUMP_IF_GREATER = 0x06
};

struct Cpu cpu_new(void);
void cpu_execute(uint16_t memory[16], struct Cpu* cpu);
void cpu_run(uint16_t memory[16], uint8_t start, struct Cpu* cpu);
