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


uint16_t CPU::little_to_big_endian(uint8_t low, uint8_t high) {
    return ((uint16_t)high << 8) + (uint16_t)low;
}


uint16_t CPU::get_IMM() {
    return registers.PC++;
}


uint16_t CPU::get_AB() {
    return little_to_big_endian(next_byte(), next_byte());
}


uint16_t CPU::get_ABX() {
    return little_to_big_endian(next_byte(), next_byte()) + registers.X;
}


uint16_t CPU::get_ABY() {
    return little_to_big_endian(next_byte(), next_byte()) + registers.Y;
}


uint16_t CPU::get_ZP() {
    return next_byte();
}


uint16_t CPU::get_ZPX() {
    return (next_byte() + registers.X) % 256;   // TODO: mod 256 - because each page is 256 bytes
}


uint16_t CPU::get_ZPY() {
    return (next_byte() + registers.Y) % 256;   // TODO: mod 256 - because each page is 256 bytes
}


uint16_t CPU::get_ACC() {
    return 0;   // unused
}


uint16_t CPU::get_IN() {
    // TODO
}


uint16_t CPU::get_INX() {
    // TODO
}


uint16_t CPU::get_INY() {
    // TODO
}


uint16_t CPU::get_REL() {
    // TODO
}



void CPU::ADC(uint16_t src) {
    uint8_t data = memory[src];
    uint16_t temp = data + registers.A + if_carry();
    set_zero(temp & 0xFF);  // Review: What is meant by this? - This is not valid in decimal mode
    if (if_decimal()) {
        if (((registers.A & 0xF) + (data & 0xF) + if_carry()) > 9)
            temp += 6;
        set_sign(temp);
        set_overflow(!((registers.A ^ data) & 0x80) && ((registers.A ^ temp) & 0x80));
        set_carry(temp > 0x99);
    } else {
        set_sign(temp);
        set_overflow(!((registers.A ^ data) & 0x80) && ((registers.A ^ temp) & 0x80));
        set_carry(temp > 0x99);
    }
    CPU_Registers.A = (uint8_t)temp;
}



void CPU::AND_helper(uint16_t src) {
    uint8_t data = memory[src];
    data &= registers.A;
    set_sign(data);
    set_zero(data);
    registers.A = data;
}


void CPU::ASL(uint16_t src) {
    uint8_t data = memory[src];
    set_carry(data & 0x80);
    data <<= 1;
    data &= 0xff;
    set_sign(data);
    set_zero(data);
    store(src, data);
}

void CPU::ASL_ACC(uint16_t src) {
    uint8_t data = registers.A;
    set_carry(data & 0x80);
    data <<= 1;
    data &= 0xff;
    set_sign(data);
    set_zero(data);
    registers.A = data;
}