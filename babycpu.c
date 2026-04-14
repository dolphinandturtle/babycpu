#include <stdio.h>
#include <stdint.h>
#include "babycpu.h"

const uint8_t OFFSET_BITS_OPERATION = 8;
const uint8_t OFFSET_BITS_REGISTER0 = 6;
const uint8_t OFFSET_BITS_REGISTER1 = 4;
const uint8_t OFFSET_BITS_ADDRESS = 0;

const uint16_t MASK_OPERATION = 0x0fff;
const uint16_t MASK_REGISTER0 = 0x00ff;
const uint16_t MASK_REGISTER1 = 0x003f;
const uint16_t MASK_ADDRESS = 0x000f;

const uint8_t SIGNAL_HALT = 0x00;
const uint8_t SIGNAL_RUN = 0x01;
const uint8_t SIGNAL_OUT_OF_MEMORY = 0x02;

struct Cpu cpu_new(void) {
    return (struct Cpu){0x0000, 0x0, {0x0}, 0};
}

static inline uint8_t decode_operation(uint16_t instruction) {
    return (instruction & MASK_OPERATION) >> OFFSET_BITS_OPERATION;
}

static inline uint8_t decode_register0(uint16_t instruction) {
    return (instruction & MASK_REGISTER0) >> OFFSET_BITS_REGISTER0;
}

static inline uint8_t decode_register1(uint16_t instruction) {
    return (instruction & MASK_REGISTER1) >> OFFSET_BITS_REGISTER1;
}

static inline uint8_t decode_address(uint16_t instruction) {
    return (instruction & MASK_ADDRESS) >> OFFSET_BITS_ADDRESS;
}

void cpu_execute(uint16_t memory[16], struct Cpu* cpu) {
    switch (decode_operation(cpu->instruction)) {
    case LOAD:
        if (decode_register0(cpu->instruction) == 3) {
            cpu->signal = 0;
        }
        else {
            cpu->registers[decode_register0(cpu->instruction)] = memory[decode_address(cpu->instruction)];
        }
        break;
    case STORE:
        memory[decode_address(cpu->instruction)] = cpu->registers[decode_register0(cpu->instruction)];
        break;
    case INCREMENT:
        cpu->registers[0] += 1;
        break;
    case ADD:
        cpu->registers[0] += cpu->registers[1];
        break;
    case SUB:
        cpu->registers[0] -= cpu->registers[1];
        break;
    case JUMP:
        cpu->counter = decode_address(cpu->instruction);
        break;
    case JUMP_IF_GREATER:
        if (cpu->registers[0] - cpu->registers[1] > 0) {
            cpu->counter = decode_address(cpu->instruction);
        }
        break;
    }
}

void machine_print(uint16_t memory[16], struct Cpu* cpu) {
    for (int i = 0; i < 16; i++) {
        if (i == cpu->counter) {
            printf("0x%04x <\n", memory[i]);
        }
        else {
            printf("0x%04x\n", memory[i]);
        }
    }
    printf("\n");
}

void cpu_run(uint16_t memory[16], uint8_t start, struct Cpu* cpu) {
    // Preparing program entry
    cpu->counter = start;
    cpu->signal = SIGNAL_RUN;
    // Program cycle
    while (cpu->signal == SIGNAL_RUN) {
        machine_print(memory, cpu);
        cpu->instruction = memory[cpu->counter++];
        cpu_execute(memory, cpu);
        if (cpu->counter >= 16 && cpu->signal != SIGNAL_HALT) {
            cpu->signal = SIGNAL_OUT_OF_MEMORY;
        }
    }
}
