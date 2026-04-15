#include <stdio.h>
#include <stdint.h>
#include "babyops.c"
#include "../include/babycpu.h"


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

struct Cpu cpu_new(void) {
    return (struct Cpu){0x0000, 0x0, {0x0}, 0, {
        [LOAD] = cpu_load,
        [STORE] = cpu_store,
        [INCREMENT] = cpu_increment,
        [ADD] = cpu_add,
        [SUB] = cpu_sub,
        [JUMP] = cpu_jump,
        [JUMP_IF_GREATER] = cpu_jump_if_greater
    }};
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

uint16_t encode_instruction(enum Op op, uint8_t reg0, uint8_t reg1, uint8_t address) {
    return ((uint8_t)op << OFFSET_BITS_OPERATION) | (reg0 << OFFSET_BITS_REGISTER0) | (reg1 << OFFSET_BITS_REGISTER1) | (address << OFFSET_BITS_ADDRESS);
}

void cpu_run(uint16_t memory[16], uint8_t start, struct Cpu* cpu) {
    // Preparing program entry
    cpu->counter = start;
    cpu->signal = SIGNAL_RUN;
    // Program cycle
    while (cpu->signal == SIGNAL_RUN) {
        machine_print(memory, cpu);
        cpu->instruction = memory[cpu->counter++];
        cpu->ops[decode_operation(cpu->instruction)](memory, cpu);
        if (cpu->counter >= 16 && cpu->signal != SIGNAL_HALT) {
            cpu->signal = SIGNAL_OUT_OF_MEMORY;
        }
    }
}
