#include<stdio.h>
#include<stdlib.h>

/* ref - https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf */

#define MEM_SIZE 1024*1024*1   
#define MEM_BASE 0x80000000

struct Memory {
    u_int8_t memory[MEM_SIZE];
};

u_int8_t mem_load_8(Memory *&memory, u_int64_t addr) {
    
}

u_int16_t mem_load_16(Memory *&memory, u_int64_t addr) {

}

u_int32_t mem_load_32(Memory *&memory, u_int64_t addr) {

}

u_int64_t mem_load_64(Memory *&memory, u_int64_t addr) {

}

void mem_store_8(Memory *&memory, u_int64_t addr, u_int64_t val) {
    
}

void mem_store_16(Memory *&memory, u_int64_t addr, u_int64_t val) {

}

void mem_store_32(Memory *&memory, u_int64_t addr, u_int64_t val) {

}

void mem_store_64(Memory *&memory, u_int64_t addr, u_int64_t val) {

}

u_int64_t mem_load(struct Memory *&memory, u_int64_t addr, u_int64_t size) {
    switch (size)
    {
    case 8:
        return mem_load_8(memory,addr);
    case 16:
        return mem_load_16(memory,addr);
    case 32:
        return mem_load_32(memory,addr);
    case 64:
        return mem_load_64(memory,addr);
    default:;
    }
    return 1;
}

void mem_store(Memory *&memory, u_int64_t addr, u_int64_t size, u_int64_t val) {
    switch (size)
    {
    case 8:
        mem_store_8(memory,addr,val);
        break;
    case 16:
        mem_store_16(memory,addr,val);
        break;
    case 32:
        mem_store_32(memory,addr,val);
        break;
    case 64:
        mem_store_64(memory,addr,val);
        break;
    default:;
    }
}

uint64_t fetch_rs1(uint32_t &instr){
    return (instr >> 15)&0x1f;
}

uint64_t fetch_rs2(uint32_t &instr){
    return (instr >> 20)&0x1f;
}

uint64_t fetch_rd(uint32_t &instr){
    return (instr >> 7)&0x1f;
}

uint64_t fetch_imm_I(uint32_t &instr){
    return ((int64_t)(int32_t)(instr&0xfff00000)) >> 20;
}

uint64_t fetch_imm_S(uint32_t &instr){
    return ((int64_t)(int32_t)(instr&0xfe00000) >> 20 ) | ((instr >> 7)&0x1f);
}

uint64_t fetch_imm_B(uint32_t &instr){
    return ((int64_t)(int32_t)(instr&0x80000000) >> 19)
            | ((instr << 4)&0x800)
            | ((instr >> 20)&0xfe0) // 1111-1110-0000
            | ((instr >> 8)&0x1e);  //      0001-1110
}

uint64_t fetch_imm_U(uint32_t &instr){
    return (int64_t)(int32_t)((instr >> 12)&0xfffff999);
}

uint64_t fetch_imm_J(uint32_t &instr){
    return (int64_t)((int64_t)(int32_t)(instr&80000000) >> 11) // 00010000 
            | (instr&0xff000)       // | 00ff000  
            | (instr >> 9)&0x800    // | 00000800
            | (instr >> 20)&0x7fe;  // | 000007fe 
}

uint32_t shamt(uint32_t &instr) {
    return (uint32_t) (fetch_imm_I(instr) & 0x1f); 
}

struct VirtualCpu* cpu_init() {
    VirtualCpu* cpu = (struct VirtualCpu *)malloc(sizeof(struct VirtualCpu));
    cpu->reg[0] = 0;
    cpu->reg[2] = MEM_BASE + MEM_SIZE;
    cpu->pc = MEM_BASE;
    return cpu;
}

struct VirtualCpu* cpu_init(VirtualCpu* cpu) {
    cpu->reg[0] = 0;
    cpu->reg[2] = MEM_BASE + MEM_SIZE;
    cpu->pc = MEM_BASE;
};

enum OPCODE{
    R_TYPE = 0x33,
    I_TYPE = 0x13,
    S_TYPE = 0x23,
    B_TYPE = 0x63,
    LOAD = 0x03,
    CSR = 0x73,
};

enum CSR{
    EBREAKCALL = 0x0,
    
};

enum B_TYPE{
    BEQ = 0x0,
    BNE = 0x1,
    BLT = 0x4,
    BGE = 0x5,
    BLTU = 0x6,
    BGEU = 0x7,
};

enum S_TYPE{
    SB = 0x0,
    SH = 0x1,
    SW = 0x2,
};

enum FUN3{
    ADD = 0x00,
    SUB = 0x00,
    XOR = 0x4,
    OR = 0x6,
    AND = 0x7,
    SLL = 0x1,
    SRL = 0x5,
    SRA = 0x5,
    SLT = 0x2,
    STLU = 0x3,
};

enum FUN7{
    ADD = 0x00,
    SUB = 0x20,
    SRA = 0x20,
};

enum LOAD{
    LB  = 0x0,
    LH  = 0x1,
    LW  = 0x2,
    LD  = 0x3,
    LBU = 0x4,
    LHU = 0x5,
    LWU = 0x6,
};


struct VirtualCpu{
    u_int64_t reg[32];
    u_int64_t pc;
    Memory *memory;
};



