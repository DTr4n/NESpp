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


void CPU::ADC(uint8_t operand) {
    uint8_t temp = operand + registers.A + (if_carry ? 1 : 0  
}
