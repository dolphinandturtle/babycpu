#include <stdint.h>

// DICTIONARY:
// op:    operation
// reg:   register
// addr:  address
// instr: instruction
// sig:   signal
// p:     pointer/counter

typedef uint8_t op_t;
typedef uint8_t ireg_t;
typedef uint8_t imem_t;
typedef uint16_t instr_t;

enum Sig {
    SIG_HALT = 0x0,
    SIG_RUN = 0x1,
    SIG_OUT_OF_MEM = 0x2
};

enum Op {
    OP_LOAD = 0x00,
    OP_STORE = 0x01,
    OP_ADD = 0x02,
    OP_SUB = 0x03,
    OP_MUL = 0x04,
    OP_JUMP = 0x05,
    OP_HALT = 0x06
};

struct Cpu {
    instr_t instr;
    imem_t imem;
    uint8_t reg[4];
    enum Sig sig;
    void (*optable[16])(instr_t*, struct Cpu*);
};

typedef void (*optable_t[16])(instr_t*, struct Cpu*);

struct Cpu cpu_new(void);
void cpu_run(uint16_t* mem, imem_t count, imem_t start, struct Cpu* cpu);
// instr_t encode_instruction(enum Op op, ireg_t ireg0, ireg_t ireg1, imem_t imem);
