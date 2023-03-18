#include<iostream>
#include"virtualcpu.hpp"

VirtualCpu::VirtualCpu() {

}


void VirtualCpu::exec_addi(uint32_t instr) {
    uint64_t imm = fetch_imm_I(instr);
    reg[fetch_rd(instr)] = reg[fetch_rs1(instr)] + (int64_t)imm; 

}

void VirtualCpu::exec_sub(uint32_t instr) {
    uint64_t imm = fetch_imm_I(instr);
    reg[fetch_rd(instr)] = reg[fetch_rs1(instr)] - (int64_t)imm; 

}

void VirtualCpu::exec_andi(uint32_t instr) {
    uint64_t imm = fetch_imm_I(instr);
    reg[fetch_rd(instr)] = reg[fetch_rs1(instr)]&(int64_t)imm; 
}

void VirtualCpu::exec_xori(uint32_t instr) {
    uint64_t imm = fetch_imm_I(instr);
    reg[fetch_rd(instr)] = reg[fetch_rs1(instr)] ^ (int64_t)imm; 
}

void VirtualCpu::exec_ori(uint32_t instr) {
    uint64_t imm = fetch_imm_I(instr);
    reg[fetch_rd(instr)] = reg[fetch_rs1(instr)] | (int64_t)imm; 
}

void VirtualCpu::exec_slli(uint32_t instr) {
    uint64_t imm = shamt(instr);
    reg[fetch_rd(instr)] = reg[fetch_rs1(instr)] << (int64_t)imm; 

}

void VirtualCpu::exec_srli(uint32_t instr) {
    uint64_t imm = fetch_imm_I(instr);
    reg[fetch_rd(instr)] = reg[fetch_rs1(instr)] >> (int64_t)imm; 
}

void VirtualCpu::exec_srai(uint32_t instr) {
    uint64_t imm = fetch_imm_I(instr);
    reg[fetch_rd(instr)] = (int32_t)reg[fetch_rs1(instr)] >> imm; 
}

void VirtualCpu::exec_sllw(uint32_t instr) {
    uint64_t imm = shamt(instr);
    reg[fetch_rd(instr)] = (int64_t)(int32_t)(reg[fetch_rs1(instr)] << (int64_t)imm); 
}

void VirtualCpu::exec_srlw(uint32_t instr) {
    uint64_t imm = fetch_imm_I(instr);
    reg[fetch_rd(instr)] = (int64_t)(int32_t)(reg[fetch_rs1(instr)] >> (int64_t)imm); 
}

void VirtualCpu::exec_sraw(uint32_t instr) {
    uint64_t imm = fetch_imm_I(instr);
    reg[fetch_rd(instr)] = (int64_t)(int32_t)(reg[fetch_rs1(instr)] >> imm); 
}

//?
void VirtualCpu::exec_slti(uint32_t instr) {
    int64_t rs1 = fetch_rs1(instr);
    int64_t imm = fetch_imm_I(instr);
    int64_t rd = fetch_rd(instr);
    if(rs1 < imm){
        reg[rd] = 1;
    }else{
        reg[rd] = 0;
    }
}
//?
void VirtualCpu::exec_sltui(uint32_t instr) {
    uint64_t rs1 = fetch_rs1(instr);
    uint64_t imm = fetch_imm_I(instr);
    uint64_t rd = fetch_rd(instr);
    if(rs1 < imm){
        reg[rd] = 1;
    }else{
        reg[rd] = 0;
    }
}


//LOAD INSTR

void VirtualCpu::exec_lb(uint32_t instr) {
    uint32_t rs1 = fetch_rs1(instr);
    uint64_t offset = (uint64_t)(reg[rs1] + (int64_t)fetch_imm_I(instr));
    uint32_t rd = fetch_rd(instr);
    reg[rd] = (int64_t)(int8_t)mem_load(offset,8);
}

void VirtualCpu::exec_lh(uint32_t instr) {
    uint32_t rs1 = fetch_rs1(instr);
    uint64_t offset = (uint64_t)(reg[rs1] + (int64_t)fetch_imm_I(instr));
    uint32_t rd = fetch_rd(instr);
    reg[rd] = (int64_t)(int16_t)mem_load(offset,16);
}

void VirtualCpu::exec_lw(uint32_t instr) {
    uint32_t rs1 = fetch_rs1(instr);
    uint64_t offset = (uint64_t)(reg[rs1] + (int64_t)fetch_imm_I(instr));
    uint32_t rd = fetch_rd(instr);
    reg[rd] = (int64_t)(int32_t)mem_load(offset,32);
}

void VirtualCpu::exec_ld(uint32_t instr){
    uint32_t rs1 = fetch_rs1(instr);
    uint64_t offset = (uint64_t)(reg[rs1] + (int64_t)fetch_imm_I(instr));
    uint32_t rd = fetch_rd(instr);
    reg[rd] = (int64_t)mem_load(offset,63);
}

void VirtualCpu::exec_lbu(uint32_t instr) {
    uint32_t rs1 = fetch_rs1(instr);
    uint64_t offset = (uint64_t)(reg[rs1] + (int64_t)fetch_imm_I(instr));
    uint32_t rd = fetch_rd(instr);
    reg[rd] = (uint64_t)mem_load(offset,8);
}

void VirtualCpu::exec_lhu(uint32_t instr) {
    uint32_t rs1 = fetch_rs1(instr);
    uint64_t offset = (uint64_t)(reg[rs1] + (int64_t)fetch_imm_I(instr));
    uint32_t rd = fetch_rd(instr);
    reg[rd] = (uint64_t)mem_load(offset,16);
}

void VirtualCpu::exec_lwu(uint32_t instr) {
    uint64_t rs1 = fetch_rs1(instr);
    uint64_t offset = (uint64_t)(reg[rs1] + (int64_t)fetch_imm_I(instr));
    uint64_t rd = fetch_rd(instr);
    reg[rd] = (uint64_t)mem_load(offset,32);
}

// STORE INSTR
void VirtualCpu::exec_sb(uint32_t instr) {
    uint64_t rs1 = fetch_rs1(instr);
    uint64_t offset = (uint64_t)(reg[rs1] + (int64_t)fetch_imm_S(instr));
    uint64_t rs2 = fetch_rs2(instr);
    mem_store(offset, 8, reg[rs2]);
}

void VirtualCpu::exec_sh(uint32_t instr) {
    uint64_t rs1 = fetch_rs1(instr);
    uint64_t offset = (uint64_t)(reg[rs1] + (int64_t)fetch_imm_S(instr));
    uint64_t rs2 = fetch_rs2(instr);
    mem_store(offset, 16, reg[rs2]);
}

void VirtualCpu::exec_sw(uint32_t instr) {
    uint64_t rs1 = fetch_rs1(instr);
    uint64_t offset = (uint64_t)(reg[rs1] + (int64_t)fetch_imm_S(instr));
    uint64_t rs2 = fetch_rs2(instr);
    mem_store(offset, 32, reg[rs2]);
}

void VirtualCpu::exec_sd(uint32_t instr) {
    uint64_t rs1 = fetch_rs1(instr);
    uint64_t offset = (uint64_t)(reg[rs1] + (int64_t)fetch_imm_S(instr));
    uint64_t rs2 = fetch_rs2(instr);
    mem_store(offset, 64, reg[rs2]);
}


// BRANCH
void VirtualCpu::exec_beq(uint32_t instr) {
    uint64_t imm = fetch_imm_B(instr);
    if((int64_t)reg[fetch_rs1(instr)] == (int64_t)reg[fetch_rs2(instr)]) {
        pc = pc + (int64_t)imm - 4;
    }
}

void VirtualCpu::exec_bne(uint32_t instr) {
    uint64_t imm = fetch_imm_B(instr);
    if((int64_t)reg[fetch_rs1(instr)] != (int64_t)reg[fetch_rs2(instr)]) {
        pc = pc + (int64_t)imm - 4;
    }
}

void VirtualCpu::exec_blt(uint32_t instr) {
    uint64_t imm = fetch_imm_B(instr);
    if((int64_t)reg[fetch_rs1(instr)] < (int64_t)reg[fetch_rs2(instr)]) {
        pc = pc + (int64_t)imm - 4;
    }
}

void VirtualCpu::exec_bge(uint32_t instr) {
    uint64_t imm = fetch_imm_B(instr);
    if((int64_t)reg[fetch_rs1(instr)] >= (int64_t)reg[fetch_rs2(instr)]) {
        pc = pc + (int64_t)imm - 4;
    }
}

void VirtualCpu::exec_bgeu(uint32_t instr) {
    uint64_t imm = fetch_imm_B(instr);
    if(reg[fetch_rs1(instr)] >= reg[fetch_rs2(instr)]) {
        pc = (int64_t) pc + (int64_t)imm - 4;
    }
}

void VirtualCpu::exec_bltu(uint32_t instr) {
    uint64_t imm = fetch_imm_B(instr);
    if(reg[fetch_rs1(instr)] < reg[fetch_rs2(instr)]) {
        pc = pc + (int64_t)imm - 4;
    }
}

void VirtualCpu::exec_csrrw(uint32_t instr) {
    uint64_t csr_val = fetch_csr(instr);
    uint64_t csr = csr_read(csr_val);
    reg[fetch_rd(instr)] = csr;
    csr_write(csr_val, reg[fetch_rs1(instr)]);
}

void VirtualCpu::exec_csrrs(uint32_t instr) {
    uint64_t csr_val = fetch_csr(instr);
    csr_write(csr_val, csr_read(csr_val)|reg[fetch_rs1(instr)]);
    
}

void VirtualCpu::exec_csrrc(uint32_t instr) {
    uint64_t csr_val = fetch_csr(instr);
    csr_write(csr_val, csr_read(csr_val)&!reg[fetch_rs1(instr)]);
}

void VirtualCpu::exec_csrrwi(uint32_t instr) {
    uint64_t csr_val = fetch_csr(instr);
    csr_write(csr_val, fetch_rs1(instr));
}

void VirtualCpu::exec_csrrsi(uint32_t instr) {
    uint64_t csr_val = fetch_csr(instr);
    csr_write(csr_val, csr_read(csr_val)|fetch_rs1(instr));
}

void VirtualCpu::exec_csrrci(uint32_t instr) {
    uint64_t csr_val = fetch_csr(instr);
    csr_write(csr_val, csr_read(csr_val)&!fetch_rs1(instr));
}

void VirtualCpu::exec_ecall(uint32_t instr) {
    uint64_t imm = fetch_imm_I(instr);
    uint64_t rs1 = fetch_rs1(instr);
    uint64_t rd = fetch_rd(instr);
    uint64_t rd = fetch_func3(instr);


}

void VirtualCpu::exec_ebreak(uint32_t instr) {

}

void VirtualCpu::exec_jal(uint32_t instr) {
    int64_t off = fetch_imm_J(instr);
    reg[fetch_rd(instr)] = pc + 4;
    pc = pc+(int64_t)off;
}

void VirtualCpu::exec_jalr(uint32_t instr) {
    uint64_t imm = fetch_rs1(instr);
    uint64_t t = pc + 4;
    pc = pc + (int64_t)reg[fetch_rs1(instr)] + ((int64_t)imm)&0xfffffffe;
    uint64_t pc = t;
}




void VirtualCpu::exec_lui(uint32_t instr) {
    reg[fetch_rd(instr)] = (uint64_t)(int64_t)(int32_t)(instr&0xfffff000);
}

void VirtualCpu::exec_auipc(uint32_t instr) {
    uint64_t imm = fetch_imm_U(instr);
    reg[fetch_rd(instr)] = ((int64_t)pc + (int64_t)imm) - 4;
}







/// R TYPE

void VirtualCpu::exec_add(uint32_t instr) {
    reg[fetch_rd(instr)] = (uint64_t)((int32_t)reg[fetch_rs1(instr)] + (int32_t)reg[fetch_rs2(instr)]);
}

void VirtualCpu::exec_sub(uint32_t instr) {
    reg[fetch_rd(instr)] = (uint64_t)((int32_t)reg[fetch_rs1(instr)] - (int32_t)reg[fetch_rs2(instr)]);
}

void VirtualCpu::exec_and(uint32_t instr) {
    reg[fetch_rd(instr)] = reg[fetch_rs1(instr)]&reg[fetch_rs2(instr)];
}

void VirtualCpu::exec_xor(uint32_t instr) {
    reg[fetch_rd(instr)] = reg[fetch_rs1(instr)]^reg[fetch_rs2(instr)];
}

void VirtualCpu::exec_or(uint32_t instr) {
    reg[fetch_rd(instr)] = reg[fetch_rs1(instr)]|reg[fetch_rs2(instr)];
}

void VirtualCpu::exec_slt(uint32_t instr) {
    int64_t rs1 = fetch_rs1(instr);
    int64_t rs2 = fetch_rs2(instr);
    int64_t rd = fetch_rd(instr);
    if(rs1 < rs2){
        reg[rd] = 1;
    }else{
        reg[rd] = 0;
    }
}

void VirtualCpu::exec_sltu(uint32_t instr) {
    uint64_t rs1 = fetch_rs1(instr);
    uint64_t rs2 = fetch_rs2(instr);
    uint64_t rd = fetch_rd(instr);
    if(rs1 < rs2){
        reg[rd] = 1;
    }else{
        reg[rd] = 0;
    }
}

void VirtualCpu::exec_sll(uint32_t instr) {
    reg[fetch_rd(instr)] = reg[fetch_rs1(instr)] << (int64_t)reg[fetch_rs2(instr)];
}

void VirtualCpu::exec_srl(uint32_t instr) {
    reg[fetch_rd(instr)] = reg[fetch_rs1(instr)] >> reg[fetch_rs2(instr)];

}

void VirtualCpu::exec_sra(uint32_t instr) {
    reg[fetch_rd(instr)] = (int32_t)reg[fetch_rs1(instr)] >> (int64_t)reg[fetch_rs2(instr)];
}


//64 RT


void VirtualCpu::exec_addw(uint32_t instr) {
    reg[fetch_rd(instr)] = (int64_t)(int32_t)reg[fetch_rs1(instr)] + (int32_t)reg[fetch_rs2(instr)];
}

void VirtualCpu::exec_subw(uint32_t instr) {
    reg[fetch_rd(instr)] = (int64_t)(int32_t)reg[fetch_rs1(instr)] - (int32_t)reg[fetch_rs2(instr)];

}

void VirtualCpu::exec_divw(uint32_t instr) {
    reg[fetch_rd(instr)] = (int64_t)(int32_t)reg[fetch_rs1(instr)] / (int32_t)reg[fetch_rs2(instr)];

}

void VirtualCpu::exec_divuw(uint32_t instr) {
    reg[fetch_rd(instr)] = (uint64_t)(int32_t)reg[fetch_rs1(instr)] / (int32_t)reg[fetch_rs2(instr)];

}

void VirtualCpu::exec_mulw(uint32_t instr) {
    reg[fetch_rd(instr)] = (int64_t)(int32_t)reg[fetch_rs1(instr)] * (int32_t)reg[fetch_rs2(instr)];

}

void VirtualCpu::exec_muluw(uint32_t instr) {
    reg[fetch_rd(instr)] = (uint64_t)(int32_t)reg[fetch_rs1(instr)] * (int32_t)reg[fetch_rs2(instr)];

}

void VirtualCpu::exec_remw(uint32_t instr) {
    reg[fetch_rd(instr)] = (int64_t)(int32_t)reg[fetch_rs1(instr)] % (int32_t)reg[fetch_rs2(instr)];

}

void VirtualCpu::exec_remuw(uint32_t instr) {
    reg[fetch_rd(instr)] = reg[fetch_rs1(instr)] % (int32_t)reg[fetch_rs2(instr)];

}

void VirtualCpu::exec_sllw(uint32_t instr) {
    reg[fetch_rd(instr)] = (int64_t)(int32_t)reg[fetch_rs1(instr)] << reg[fetch_rs2(instr)];

}

void VirtualCpu::exec_srlw(uint32_t instr) {
    reg[fetch_rd(instr)] = (int64_t)(int32_t)reg[fetch_rs1(instr)] >> reg[fetch_rs2(instr)];

}

void VirtualCpu::exec_sraw(uint32_t instr) {
    reg[fetch_rd(instr)] = (int64_t)(int32_t)reg[fetch_rs1(instr)] >> (uint64_t)reg[fetch_rs2(instr)];

}





int VirtualCpu::execute(uint32_t instr) {
        uint32_t op = instr&0x7f;
        uint64_t func3 = (instr >> 12)&0x7;
        uint64_t func7 = (instr >> 12)&0x7f;
        switch(op){
            case I_TYPE:  
            {        
                switch (func3) {
                    case ADD:  exec_addi(instr); break;
                    case SLL:  exec_slli(instr); break;
                    case SLT:  exec_slti(instr); break;
                    case SLTU: exec_sltui(instr); break;
                    case XOR:  exec_xori(instr); break;
                    case SR:   
                        switch (func7) {
                            case SRL:  exec_srli(instr); break;
                            case SRA:  exec_srai(instr); break;
                            default: ;
                        } break;
                    case OR:   exec_ori(instr); break;
                    case AND:  exec_andi(instr); break;
                    default:
                        fprintf(stderr, 
                                "[-] ERROR-> opcode:0x%x, funct3:0x%x, funct7:0x%x\n"
                                , op, func3, func7);
                        return 0;
                } break;
            }
            case R_TYPE:
            {
                switch (func3) {
                case ADD:
                case SUB:
                    switch (func7) {
                        case ADD: exec_add(instr);
                        case SUB: exec_sub(instr);
                        default: ;
                    } break;
                case SLL:  exec_sll(instr); break;
                case SLT:  exec_slt(instr); break;
                case SLTU: exec_sltu(instr); break;
                case XOR:  exec_xor(instr); break;
                case SR:   
                    switch (func7) {
                        case SRL:  exec_srl(instr); break;
                        case SRA:  exec_sra(instr); break;
                        default: ;
                    }
                case OR:   exec_or(instr); break;
                case AND:  exec_and(instr); break;
                default:
                    fprintf(stderr, 
                            "[-] ERROR-> opcode:0x%x, funct3:0x%x, funct7:0x%x\n"
                            , op, func3, func7);
                    return 0;
                } break;
            }
            case R_TYPE_64:
            {
                switch (func3) {
                case ADD:
                case SUB:
                    switch (func7) {
                        case ADD: exec_addw(instr);
                        case MUL: exec_addw(instr);
                        case SUB: exec_subw(instr);
                        default: ;
                    } break;
                case SLL:  exec_sllw(instr); break;
                case SLT:  exec_sltw(instr); break;
                case SLTU: exec_sltuw(instr); break;
                case XOR:  exec_xorw(instr); break;
                case SR:   
                    switch (func7) {
                        case SRL:  exec_srlw(instr); break;
                        case SRA:  exec_sraw(instr); break;
                        default: ;
                    }
                case OR:   exec_orw(instr); break;
                case AND:  exec_andw(instr); break;
                default:
                    fprintf(stderr, 
                            "[-] ERROR-> opcode:0x%x, funct3:0x%x, funct7:0x%x\n"
                            , op, func3, func7);
                    return 0;
                } break;
            }
            case LOAD: 
            {
                switch (func3)
                {
                case LB:
                {
                    exec_lb(instr);
                    break;
                }
                case LH:
                {
                    exec_lh(instr);
                    break;
                }
                case LW:
                {
                    exec_lw(instr);
                    break;
                }
                case LD:
                {
                    exec_ld(instr);
                    break;
                }
                case LBU:
                {
                    exec_lbu(instr);
                    break;
                }
                case LHU:
                {
                    exec_lhu(instr);
                    break;
                }
                case LWU:
                {
                    exec_lwu(instr);
                    break;
                }
                default:
                    break;
                }
            }
            case B_TYPE:
            {
                switch (func3)
                {
                case BEQ:
                {
                    exec_beq(instr);
                    break;
                }
                case BNE:
                {
                    exec_bne(instr);
                    break;
                }
                case BLT:
                {
                    exec_blt(instr);
                    break;
                }
                case BGE:
                {
                     exec_bge(instr);
                    break;
                }
                case BLTU:
                {
                     exec_bltu(instr);
                    break;
                }
                case BGEU:
                {
                     exec_bgeu(instr);
                    break;
                }
                
                default:
                    break;
                }
            }
            
            

        }
}
