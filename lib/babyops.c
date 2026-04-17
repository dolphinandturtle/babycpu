#include "../include/babycpu.h"

// #define DEBUG

// Bit offsets
const uint8_t DBITS_REG0 = 10;
const uint8_t DBITS_REG1 = 8;
const uint8_t DBITS_ADDR = 0;

// Bit mask
const uint16_t MASK_REG0 = 0x0fff;
const uint16_t MASK_REG1 = 0x03ff;
const uint16_t MASK_ADDR = 0x00ff;

static inline ireg_t dec_ireg0(instr_t instr) {
    return (instr & MASK_REG0) >> DBITS_REG0;
}

static inline ireg_t dec_ireg1(instr_t instr) {
    return (instr & MASK_REG1) >> DBITS_REG1;
}

static inline imem_t dec_imem(instr_t instr) {
    return (instr & MASK_ADDR) >> DBITS_ADDR;
}

void cpu_load(uint16_t mem[256], struct Cpu* cpu) {
    ireg_t ireg0 = dec_ireg0(cpu->instr);
    ireg_t ireg1 = dec_ireg1(cpu->instr);
    imem_t imem_or_val = dec_imem(cpu->instr);
    switch (ireg1) {
    case 0x0:
        cpu->reg[ireg0] = mem[imem_or_val];
        break;
    case 0x1:
        cpu->reg[ireg0] = imem_or_val;
        break;
    case 0x2:
        cpu->reg[ireg0] = mem[cpu->reg[ireg1]];
        break;
    case 0x3:
        switch (ireg0) {
        case 0x0:
            cpu->reg[3] = cpu->reg[1];
            break;
        case 0x1:
            cpu->reg[1] = cpu->reg[2];
            break;
        case 0x2:
            cpu->reg[2] = cpu->reg[3];
            break;
        case 0x3:
            cpu->reg[3] = cpu->reg[4];
            break;
        }
        break;
    }
}

void cpu_store(uint16_t mem[256], struct Cpu* cpu) {
    ireg_t ireg0 = dec_ireg0(cpu->instr);
    ireg_t ireg1 = dec_ireg1(cpu->instr);
    imem_t imem = dec_imem(cpu->instr);
    switch (ireg1) {
    case 0x0:
        mem[imem] = cpu->reg[ireg0];
        break;
    case 0x1:
        mem[imem] = cpu->reg[ireg0];
        break;
    case 0x2:
        mem[cpu->reg[ireg1]] = cpu->reg[ireg0];
        break;
    case 0x3:
        mem[cpu->reg[ireg1]] = cpu->reg[ireg0];
        break;
    }
}

void cpu_add(uint16_t mem[256], struct Cpu* cpu) {
    ireg_t ireg0 = dec_ireg0(cpu->instr);
    ireg_t ireg1 = dec_ireg1(cpu->instr);
    cpu->reg[ireg0] += cpu->reg[ireg1];
}

void cpu_sub(uint16_t mem[256], struct Cpu* cpu) {
    ireg_t ireg0 = dec_ireg0(cpu->instr);
    ireg_t ireg1 = dec_ireg1(cpu->instr);
    cpu->reg[ireg0] += cpu->reg[ireg1];
}

void cpu_mul(uint16_t mem[256], struct Cpu* cpu) {
    ireg_t ireg0 = dec_ireg0(cpu->instr);
    ireg_t ireg1 = dec_ireg1(cpu->instr);
    cpu->reg[ireg0] += cpu->reg[ireg1];
}

void cpu_jump(uint16_t mem[256], struct Cpu* cpu) {
    ireg_t ireg0 = dec_ireg0(cpu->instr);
    ireg_t ireg1 = dec_ireg1(cpu->instr);
    imem_t imem = dec_imem(cpu->instr);
    #ifdef DEBUG
    printf("%d > %d\n", cpu->reg[ireg0], cpu->reg[ireg1]);
    #endif
    if (cpu->reg[ireg0] > cpu->reg[ireg1]) {
        cpu->imem = imem;
    }
}

void cpu_halt(uint16_t mem[256], struct Cpu* cpu) {
    cpu->sig = SIG_HALT;
}
