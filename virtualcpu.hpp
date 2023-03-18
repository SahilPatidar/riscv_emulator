#pragma once
#include<iostream>


#define MEM_SIZE 1024*1024*1   
#define MEM_BASE 0x80000000

class Memory {
    private:
    u_int8_t memory[MEM_SIZE];
    uint64_t csr[4096];
    public:

    bool read_file(char *filename);
    u_int16_t mem_load_8(u_int64_t addr);
    u_int16_t mem_load_16(u_int64_t addr);
    u_int32_t mem_load_32(u_int64_t addr);
    u_int64_t mem_load_64(u_int64_t addr);
    

    void mem_store_8(u_int64_t addr, u_int64_t val);
    void mem_store_16(u_int64_t addr, u_int64_t val);
    void mem_store_32(u_int64_t addr, u_int64_t val);
    void mem_store_64(u_int64_t addr, u_int64_t val);

    uint64_t csr_read(uint64_t off) {
        return (uint64_t)(uint32_t)csr[off];
    }

    void csr_write(uint64_t off, uint64_t val) {
        csr[off] = val;
    }

    u_int64_t mem_load(u_int64_t addr, u_int64_t size) {
        switch (size)
        {
        case 8:
            return mem_load_8(addr);
        case 16:
            return mem_load_16(addr);
        case 32:
            return mem_load_32(addr);
        case 64:
            return mem_load_64(addr);
        default:;
        }
        return 1;
    }

    void mem_store(u_int64_t addr, u_int64_t size, u_int64_t val) {
        switch (size)
        {
        case 8:
            mem_store_8(addr,val);
            break;
        case 16:
            mem_store_16(addr,val);
            break;
        case 32:
            mem_store_32(addr,val);
            break;
        case 64:
            mem_store_64(addr,val);
            break;
        default:;
        }
    }

};


class Decoder {
    public:
    
    uint64_t fetch_rs1(uint32_t &instr){
        return (instr >> 15)&0x1f;
    }
    
    uint64_t fetch_func3(uint32_t &instr){
        return (instr >> 12)&0x7;
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
    
    uint64_t fetch_csr(uint32_t &instr){
        return (instr&0xfff00000) >> 20;
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
        return (int64_t)(int32_t)(instr&&0xfffff999);
    }

    uint64_t fetch_imm_J(uint32_t &instr){
        return (uint64_t)((int64_t)(int32_t)(instr&80000000) >> 11) // 00010000 
                | (instr&0xff000)       // | 00ff000  
                | (instr >> 9)&0x800    // | 00000800
                | (instr >> 20)&0x7fe;  // | 000007fe 
    }

    uint32_t shamt(uint32_t &instr) {
        return (uint32_t) (fetch_imm_I(instr) & 0x1f); 
    }                                                 

};

enum OPCODE{
    R_TYPE = 0x33,
    I_TYPE = 0x13,
    S_TYPE = 0x23,
    B_TYPE = 0x63,
    I_TYPE_64 = 0x1b,
    R_TYPE_64 = 0x3b,
    LOAD = 0x03,
    CSR = 0x73,
    LUI  =  0x37, 
    AUIPC = 0x17, 
    JAL   = 0x6f, 
    JALR  = 0x67, 
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
    SD = 0x3,
};

enum FUN3{
    ADD = 0x00,
    SUB = 0x00,
    XOR = 0x4,
    OR = 0x6,
    AND = 0x7,
    SLL = 0x1,
    SR = 0x5,
    SLT = 0x2,
    SLTU = 0x3,
};

enum FUN7{
    ADD = 0x00,
    MUL = 0x01,
    SUB = 0x20,
    SRL = 0x00,
    SRA = 0x20,
};

enum FUN3_64{
    ADDW = 0x0,
    SUBW = 0x0,
    SLLW = 0x1,
    SRW  = 0x5,
    REMW  = 0x6,
    REMUW = 0x7,
    DIVW = 0x4,
};

enum FUN7_64{
    SRLW = 0x00,
    DIVUW = 0x01,
    SRAW = 0x20,
    ADDW = 0x00,
    MULW = 0x01,
    SUBW = 0x20,
    SRLW = 0x00,
    SRAW = 0x20,
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

class VirtualCpu: public Memory, Decoder  {
    private:
    u_int64_t reg[32];
    u_int64_t pc;
    
    public:
    VirtualCpu()
    :pc(MEM_BASE)
    {
        reg[0] = 0;
        reg[2] = MEM_BASE + MEM_SIZE;
    }
    
    void pc_inc(){
        pc+=4;
    }

    void exec_sub(uint32_t instr);

    void exec_addi(uint32_t instr);
    void exec_andi(uint32_t instr);
    void exec_xori(uint32_t instr);
    void exec_ori(uint32_t instr);
    void exec_slli(uint32_t instr);
    void exec_srli(uint32_t instr);
    void exec_srai(uint32_t instr);
    void exec_slti(uint32_t instr);
    void exec_sltui(uint32_t instr);

    void exec_addw(uint32_t instr);
    void exec_subw(uint32_t instr);
    void exec_divw(uint32_t instr);
    void exec_divuw(uint32_t instr);
    void exec_mulw(uint32_t instr);
    void exec_muluw(uint32_t instr);
    void exec_remw(uint32_t instr);
    void exec_remuw(uint32_t instr);
    void exec_sllw(uint32_t instr);
    void exec_srlw(uint32_t instr);
    void exec_sraw(uint32_t instr);

    void exec_add(uint32_t instr);
    void exec_sub(uint32_t instr);
    void exec_and(uint32_t instr);
    void exec_xor(uint32_t instr);
    void exec_or(uint32_t instr);
    void exec_slt(uint32_t instr);
    void exec_sltu(uint32_t instr);
    void exec_sll(uint32_t instr);
    void exec_srl(uint32_t instr);
    void exec_sra(uint32_t instr);


    void exec_beq(uint32_t instr);
    void exec_bne(uint32_t instr);
    void exec_blt(uint32_t instr);
    void exec_bge(uint32_t instr);
    void exec_bltu(uint32_t instr);
    void exec_bgeu(uint32_t instr);

    void exec_lb(uint32_t instr);
    void exec_lh(uint32_t instr);
    void exec_lw(uint32_t instr);
    void exec_ld(uint32_t instr);
    void exec_lbu(uint32_t instr);
    void exec_lhu(uint32_t instr);
    void exec_lwu(uint32_t instr);

    void exec_csrrw(uint32_t instr);
    void exec_csrrs(uint32_t instr);
    void exec_csrrc(uint32_t instr);
    void exec_csrrwi(uint32_t instr);
    void exec_csrrsi(uint32_t instr);
    void exec_csrrci(uint32_t instr);

    void exec_sb(uint32_t instr);
    void exec_sh(uint32_t instr);
    void exec_sw(uint32_t instr);
    void exec_sd(uint32_t instr);

    void exec_ecall(uint32_t instr);
    void exec_ebreak(uint32_t instr);
    
    void exec_lui(uint32_t instr);
    void exec_auipc(uint32_t instr);
    
    void exec_jal(uint32_t instr);
    void exec_jalr(uint32_t instr);



    int execute(uint32_t instr);
};
