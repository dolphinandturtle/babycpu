#include <stdio.h>
#include <stdint.h>
#include "babyops.c"
#include "../include/babycpu.h"

// Bit offsets
const uint8_t DBITS_OP = 12;

// Bit masks
const uint16_t MASK_OP = 0xffff;

static inline op_t dec_op(instr_t instr) {
    return (instr & MASK_OP) >> DBITS_OP;
}

struct Cpu cpu_new(void) {
    return (struct Cpu){
        0x0000, 0x0, {0x0}, 0, {
            [OP_LOAD] = cpu_load,
            [OP_STORE] = cpu_store,
            [OP_ADD] = cpu_add,
            [OP_SUB] = cpu_sub,
            [OP_MUL] = cpu_mul,
            [OP_JUMP] = cpu_jump,
            [OP_HALT] = cpu_halt
        }};
}

void machine_print(uint16_t* mem, imem_t count, struct Cpu* cpu) {
    for (int i = 0; i < count; i++) {
        if (i == cpu->imem) {
            printf("0x%04x <\n", mem[i]);
        }
        else {
            printf("0x%04x\n", mem[i]);
        }
    }
    printf("\n");
}

// instr_t encode_instruction(enum Op op, ireg_t ireg0, ireg_t ireg1, imem_t imem) {
//     return ((op_t)op << DBITS_OP) | (ireg0 << DBITS_REG0) | (ireg1 << DBITS_REG1) | (imem << DBITS_ADDR);
// }

void cpu_run(uint16_t* mem, imem_t count, imem_t start, struct Cpu* cpu) {
    // Preparing program entry
    cpu->imem = start;
    cpu->sig = SIG_RUN;
    // Program cycle
    while (cpu->sig == SIG_RUN) {
        machine_print(mem, count, cpu);
        cpu->instr = mem[cpu->imem++];
        cpu->optable[dec_op(cpu->instr)](mem, cpu);
        if (cpu->imem >= count && cpu->sig != SIG_HALT) {
            cpu->sig = SIG_OUT_OF_MEM;
        }
    }
}
