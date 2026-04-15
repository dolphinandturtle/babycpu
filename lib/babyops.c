#include "../include/babycpu.h"

void cpu_load(uint16_t memory[16], struct Cpu* cpu) {
    if (decode_register0(cpu->instruction) == 3) {
        cpu->signal = 0;
    }
    else {
        cpu->registers[decode_register0(cpu->instruction)] = memory[decode_address(cpu->instruction)];
    }
}

void cpu_store(uint16_t memory[16], struct Cpu* cpu) {
    memory[decode_address(cpu->instruction)] = cpu->registers[decode_register0(cpu->instruction)];
}

void cpu_increment(uint16_t memory[16], struct Cpu* cpu) {
    cpu->registers[0] += 1;
}

void cpu_add(uint16_t memory[16], struct Cpu* cpu) {
    cpu->registers[0] += cpu->registers[1];
}

void cpu_sub(uint16_t memory[16], struct Cpu* cpu) {
    cpu->registers[0] -= cpu->registers[1];
}

void cpu_jump(uint16_t memory[16], struct Cpu* cpu) {
    cpu->counter = decode_address(cpu->instruction);
}

void cpu_jump_if_greater(uint16_t memory[16], struct Cpu* cpu) {
    if (cpu->registers[0] - cpu->registers[1] > 0) {
        cpu->counter = decode_address(cpu->instruction);
    }
}
