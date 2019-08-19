#include "CPU.h"


bool CPU::if_carry() {
    return registers.P & 0x1; 
}


bool CPU::if_zero() {
    return (registers.P >> 1) & 0x1;
}


bool CPU::if_interrupt() {
    return (registers.P >> 2) & 0x1;
}
       

bool CPU::if_decimal() {
    return (registers.P >> 3) & 0x1;
}


bool CPU::if_break() {
    return (registers.P >> 4) & 0x1;
}


bool CPU::if_overflow() {
    return (registers.P >> 6) & 0x1;
}


bool CPU::if_sign() {
    return (registers.P >> 7) & 0x1;
}


void CPU::set_carry(bool condition) {
    if (condition)
        registers.P |= 0x1;
    else
        registers.P &= ~(0x1);
}


void CPU::set_zero(uint8_t src) {
    if (src == 0)
        registers.P |= 0x1 << 1;
    else
        registers.P &= ~(0x1 << 1);
}


void CPU::set_interrupt(bool condition) {
    if (condition)
        registers.P |= 0x1 << 2;
    else
        registers.P &= ~(0x1 << 2);
}


void CPU::set_decimal(bool condition) {
    if (condition)
        registers.P |= 0x1 << 3;
    else
        registers.P &= ~(0x1 << 3);
}


void CPU::set_break(bool condition) {
    if (condition)
        registers.P |= 0x1 << 4;
    else
        registers.P &= ~(0x1 << 4);
}


void CPU::set_overflow(bool condition) {
    if (condition)
        registers.P |= 0x1 << 6;
    else
        registers.P &= ~(0x1 << 6);
}


void CPU::set_sign(uint8_t src) {
    registers.P |= ((src >> 7) & 0x1) << 7;
}


uint16_t CPU::rel_addr(uint8_t src) {
    return src + registers.PC;
}


uint8_t CPU::load(uint16_t addr) {
    return memory[addr];
}


void CPU::store(uint16_t addr, uint8_t data) {
    memory[addr] = data;
}


uint8_t CPU::next_byte() {
    return memory[registers.PC++];
}


uint16_t little_to_big_endian(uint8_t lsb, uint8_t msb) {
    return ((uint16_t)msb << 8) + (uint16_t)lsb;
}


void CPU::ADC_IMM() {
    ADC_helper(next_byte());
}


void CPU::ADC_ZP() {
    ADC_helper(memory[next_byte()]);
}


void CPU::ADC_ZPX() {
    ADC_helper(memory[next_byte() + (uint16_t)registers.X]);
}


void CPU::ADC_AB() {
    uint8_t lsb = next_byte();
    uint8_t msb = next_byte();
    ADC_helper(memory[little_to_big_endian(lsb, msb)]);
}


void CPU::ADC_ABX() {
    uint8_t lsb = next_byte();
    uint8_t msb = next_byte();
    ADC_helper(memory[little_to_big_endian(lsb, msb) + (uint16_t)registers.X]);
}


void CPU::ADC_ABY() {
    uint8_t lsb = next_byte();
    uint8_t msb = next_byte();
    ADC_helper(memory[little_to_big_endian(lsb, msb) + (uint16_t)registers.Y]);
}


void CPU::ADC_INX() {
    ADC_helper(memory[registers.X]); // TODO: Wrong?
}


void CPU::ADC_INY() {
    ADC_helper(memory[registers.Y]); // TODO: Wrong?
}


void CPU::ADC_helper(uint8_t src) {
    uint16_t temp = src + registers.A + if_carry();
    set_zero(temp & 0xFF);  // Review: What is meant by this? - This is not valid in decimal mode
    if (if_decimal()) {
        if (((registers.A & 0xF) + (src & 0xF) + if_carry()) > 9)
            temp += 6;
        set_sign(temp);
        set_overflow(!((registers.A ^ src) & 0x80) && ((registers.A ^ temp) & 0x80));
        set_carry(temp > 0x99);
    } else {
        set_sign(temp);
        set_overflow(!((registers.A ^ src) & 0x80) && ((registers.A ^ temp) & 0x80));
        set_carry(temp > 0x99);
    }
    CPU_Registers.A = (uint8_t)temp;
}


void CPU::AND_IMM() {

}


void CPU::AND_ZP() {

}


void CPU::AND_ZPX() {

}


void CPU::AND_AB() {

}


void CPU::AND_ABX() {

}


void CPU::AND_ABY() {

}


void CPU::AND_INX() {

}


void CPU::AND_INY() {

}


void CPU::AND_helper(uint8_t src) {
    src &= registers.A;
    set_sign(src);
    set_zero(src);
    registers.A = src;
}


void CPU::ASL_ACC() {

}


void CPU::ASL_ZP() {

}


void CPU::ASL_ZPX() {

}


void CPU::ASL_AB() {

}


void CPU::ASL_ABX() {

}


void CPU::ASL_helper(uint8_t src) {
    set_carry(src & 0x80);
    src <<= 1;
    src &= 0xff;
    set_sign(src);
    set_zero(src);
}


void CPU::BCC_REL() {
    if (!if_carry()) {
        registers.PC = rel
    }
}



void CPU::BCS_REL() {

}



void CPU::BEQ_REL() {

}



void CPU::BIT_ZP() {

}


void CPU::BIT_AB() {

}



void CPU::BMI_REL() {

}



void CPU::BNE_REL() {

}



void CPU::BPL_REL() {

}



void CPU::BVC_REL() {

}



void CPU::BVS_REL() {

}



void CPU::CLC() {

}



void CPU::CLD() {

}



void CPU::CLI() {

}



void CPU::CLV() {

}



void CPU::CMP_IMM() {

}


void CPU::CMP_ZP() {

}


void CPU::CMP_ZPX() {

}


void CPU::CMP_AB() {

}


void CPU::CMP_ABX() {

}


void CPU::CMP_ABY() {

}


void CPU::CMP_INX() {

}


void CPU::CMP_INY() {

}



void CPU::CPX_IMM() {

}


void CPU::CPX_ZP() {

}


void CPU::CPX_AB() {

}



void CPU::CPY_IMM() {

}


void CPU::CPY_ZP() {

}


void CPU::CPY_AB() {

}



void CPU::DEC_ZP() {

}


void CPU::DEC_ZPX() {

}


void CPU::DEC_AB() {

}


void CPU::DEC_ABX() {

}



void CPU::DEX() {

}



void CPU::DEY() {

}



void CPU::EOR_IMM() {

}


void CPU::EOR_ZP() {

}


void CPU::EOR_ZPX() {

}


void CPU::EOR_AB() {

}


void CPU::EOR_ABX() {

}


void CPU::EOR_ABY() {

}


void CPU::EOR_INX() {

}


void CPU::EOR_INY() {

}



// INC - increment memory by one
void CPU::INC_ZP() {

}


void CPU::INC_ZPX() {

}


void CPU::INC_AB() {

}


void CPU::INC_ABX() {

}



// INX - increment index X by one
void CPU::INX() {

}



// INY - increment index Y by one
void CPU::INY() {

}



// JMP - jump to new location
void CPU::JMP_AB() {

}


void CPU::JMP_IN() {

}



void CPU::JSR_AB() {

}



void CPU::LDA_IMM() {

}


void CPU::LDA_ZP() {

}


void CPU::LDA_ZPX() {

}


void CPU::LDA_AB() {

}


void CPU::LDA_ABX() {

}


void CPU::LDA_ABY() {

}


void CPU::LDA_INX() {

}


void CPU::LDA_INY() {

}



void CPU::LDX_IMM() {

}


void CPU::LDX_ZP() {

}


void CPU::LDX_ZPY() {

}


void CPU::LDX_AB() {

}


void CPU::LDX_ABY() {

}



void CPU::LDY_IMM() {

}


void CPU::LDY_ZP() {

}


void CPU::LDY_ZPX() {

}


void CPU::LDY_AB() {

}


void CPU::LDY_ABX() {

}



void CPU::LSR_ACC() {

}


void CPU::LSR_ZP() {

}


void CPU::LSR_ZPX() {

}


void CPU::LSR_AB() {

}


void CPU::LSR_ABX() {

}



void CPU::NOP() {

}



void CPU::ORA_IMM() {

}


void CPU::ORA_ZP() {

}


void CPU::ORA_ZPX() {

}


void CPU::ORA_AB() {

}


void CPU::ORA_ABX() {

}


void CPU::ORA_ABY() {

}


void CPU::ORA_INX() {

}


void CPU::ORA_INY() {

}



void CPU::PHA() {

}



void CPU::PHP() {

}



void CPU::PLA() {

}



void CPU::PLP() {

}



void CPU::ROL_ACC() {

}


void CPU::ROL_ZP() {

}


void CPU::ROL_ZPX() {

}


void CPU::ROL_AB() {

}


void CPU::ROL_ABX() {

}



void CPU::ROR_ACC() {

}


void CPU::ROR_ZP() {

}


void CPU::ROR_ZPX() {

}


void CPU::ROR_AB() {

}


void CPU::ROR_ABX() {

}



void CPU::RTI() {

}



void CPU::RTS() {

}



void CPU::SBC_IMM() {

}


void CPU::SBC_ZP() {

}


void CPU::SBC_ZPX() {

}


void CPU::SBC_AB() {

}


void CPU::SBC_ABX() {

}


void CPU::SBC_ABY() {

}


void CPU::SBC_INX() {

}


void CPU::SBC_INY() {

}



void CPU::SEC() {

}



void CPU::SED() {

}



void CPU::SEI() {

}



void CPU::STA_ZP() {

}


void CPU::STA_ZPX() {

}


void CPU::STA_AB() {

}


void CPU::STA_ABX() {

}


void CPU::STA_ABY() {

}


void CPU::STA_INX() {

}


void CPU::STA_INY() {

}



void CPU::STX_ZP() {

}


void CPU::STX_ZPY() {

}


void CPU::STX_AB() {

}



void CPU::STY_ZP() {

}


void CPU::STY_ZPX() {

}


void CPU::STY_AB() {

}



void CPU::TAX() {

}



void CPU::TAY() {

}



void CPU::TSX() {

}



void CPU::TXA() {

}




void CPU::TXS() {

}



void CPU::TYA() {

}