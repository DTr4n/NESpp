#include "../include/CPU.h"


CPU::CPU(uint16_t initial_PC) {
    registers = {0, 0, 0, initial_PC, 0, 0};
}


void CPU::power_on() {
    std::ofstream debug_file;
    debug_file.open("debug_output.txt");
    for(;;)
        execute(debug_file);
    debug_file.close();
}


void CPU::execute(std::ofstream debug_file) {
    uint8_t fetch_byte = next_byte();
    debug_file << fetch_byte << std::endl;

    try {
        switch(fetch_byte) {
            case 0x69: ADC(get_IMM());
            case 0x65: ADC(get_ZP());
            case 0x75: ADC(get_ZPX());
            case 0x6D: ADC(get_AB());
            case 0x7D: ADC(get_ABX());
            case 0x79: ADC(get_ABY());
            case 0x61: ADC(get_INX());
            case 0x71: ADC(get_INY());
            case 0x29: AND(get_IMM());
            case 0x25: AND(get_ZP());
            case 0x35: AND(get_ZPX());
            case 0x2D: AND(get_AB());
            case 0x3D: AND(get_ABX());
            case 0x39: AND(get_ABY());
            case 0x21: AND(get_INX());
            case 0x31: AND(get_INY());
            case 0x0A: ASL_ACC();
            case 0x06: ASL(get_ZP());
            case 0x16: ASL(get_ZPX());
            case 0x0E: ASL(get_AB());
            case 0x1E: ASL(get_ABX());
            case 0x90: BCC(get_REL());
            case 0xB0: BCS(get_REL());
            case 0xF0: BEQ(get_REL());
            case 0x24: BIT(get_ZP());
            case 0x2C: BIT(get_AB());
            case 0x30: BMI(get_REL());
            case 0xD0: BNE(get_REL());
            case 0x10: BPL(get_REL());
            case 0x00: BRK();
            case 0x50: BVC(get_REL());
            case 0x70: BVS(get_REL());
            case 0x18: CLC();
            case 0xD8: CLD();
            case 0x58: CLI();
            case 0xB8: CLV();
            case 0xC9: CMP(get_IMM());
            case 0xC5: CMP(get_ZP());
            case 0xD5: CMP(get_ZPX());
            case 0xCD: CMP(get_AB());
            case 0xDD: CMP(get_ABX());
            case 0xD9: CMP(get_ABY());
            case 0xC1: CMP(get_INX());
            case 0xD1: CMP(get_INY());
            case 0xE0: CPX(get_IMM());
            case 0xE4: CPX(get_ZP());
            case 0xEC: CPX(get_AB());
            case 0xC0: CPY(get_IMM());
            case 0xC4: CPY(get_ZP());
            case 0xCC: CPY(get_AB());
            case 0xC6: DEC(get_ZP());
            case 0xD6: DEC(get_ZPX());
            case 0xCE: DEC(get_AB());
            case 0xDE: DEC(get_ABX());
            case 0xCA: DEX();
            case 0x88: DEY();
            case 0x49: EOR(get_IMM());
            case 0x45: EOR(get_ZP());
            case 0x55: EOR(get_ZPX());
            case 0x4D: EOR(get_AB());
            case 0x5D: EOR(get_ABX());
            case 0x59: EOR(get_ABY());
            case 0x41: EOR(get_INX());
            case 0x51: EOR(get_INY());
            case 0xE6: INC(get_ZP());
            case 0xF6: INC(get_ZPX());
            case 0xEE: INC(get_AB());
            case 0xFE: INC(get_ABX());
            case 0xE8: INX();
            case 0xC8: INY();
            case 0x6C: JMP(get_IN());
            case 0x4C: JMP(get_AB());
            case 0x20: JSR(get_AB());
            case 0xA9: LDA(get_IMM());
            case 0xA5: LDA(get_ZP());
            case 0xB5: LDA(get_ZPX());
            case 0xAD: LDA(get_AB());
            case 0xBD: LDA(get_ABX());
            case 0xB9: LDA(get_ABY());
            case 0xA1: LDA(get_INX());
            case 0xB1: LDA(get_INY());
            case 0xA6: LDX(get_ZP());
            case 0xB6: LDX(get_ZPY());
            case 0xAE: LDX(get_AB());
            case 0xBE: LDX(get_ABY());
            case 0xA2: LDX(get_IMM());
            case 0xA0: LDY(get_IMM());
            case 0xA4: LDY(get_ZP());
            case 0xB4: LDY(get_ZPX());
            case 0xAC: LDY(get_AB());
            case 0xBC: LDY(get_ABX());
            case 0x4A: LSR_ACC();
            case 0x46: LSR(get_ZP());
            case 0x56: LSR(get_ZPX());
            case 0x4E: LSR(get_AB());
            case 0x5E: LSR(get_ABX());
            case 0xEA: NOP();
            case 0x09: ORA(get_IMM());
            case 0x05: ORA(get_ZP());
            case 0x15: ORA(get_ZPX());
            case 0x0D: ORA(get_AB());
            case 0x1D: ORA(get_ABX());
            case 0x19: ORA(get_ABY());
            case 0x01: ORA(get_INX());
            case 0x11: ORA(get_INY());
            case 0x48: PHA();
            case 0x08: PHP();
            case 0x68: PLA();
            case 0x28: PLP();
            case 0x2A: ROL_ACC();
            case 0x26: ROL(get_ZP());
            case 0x36: ROL(get_ZPX());
            case 0x2E: ROL(get_AB());
            case 0x3E: ROL(get_ABX());
            case 0x6A: ROR_ACC();
            case 0x66: ROR(get_ZP());
            case 0x76: ROR(get_ZPX());
            case 0x6E: ROR(get_AB());
            case 0x7E: ROR(get_ABX());
            case 0x40: RTI();
            case 0x60: RTS();
            case 0xE9: SBC(get_IMM());
            case 0xE5: SBC(get_ZP());
            case 0xF5: SBC(get_ZPX());
            case 0xED: SBC(get_AB());
            case 0xFD: SBC(get_ABX());
            case 0xF9: SBC(get_ABY());
            case 0xE1: SBC(get_INX());
            case 0xF1: SBC(get_INY());
            case 0x38: SEC();
            case 0xF8: SED();
            case 0x78: SEI();
            case 0x85: STA(get_ZP());
            case 0x95: STA(get_ZPX());
            case 0x8D: STA(get_AB());
            case 0x9D: STA(get_ABX());
            case 0x99: STA(get_ABY());
            case 0x81: STA(get_INX());
            case 0x91: STA(get_INY());
            case 0x86: STX(get_ZP());
            case 0x96: STX(get_ZPY());
            case 0x8E: STX(get_AB());
            case 0x84: STY(get_ZP());
            case 0x94: STY(get_ZPX());
            case 0x8C: STY(get_AB());
            case 0xAA: TAX();
            case 0xA8: TAY();
            case 0xBA: TSX();
            case 0x8A: TXA();
            case 0x9A: TXS();
            case 0x98: TYA();
            default:
                printf("Invalid opcode");
                return NOP();
        }
    }
    catch(...) {
    }
}


bool CPU::if_carry() const {
    return registers.P & 0x1;
}


bool CPU::if_zero() const {
    return (registers.P >> 1) & 0x1;
}


bool CPU::if_interrupt() const {
    return (registers.P >> 2) & 0x1;
}


bool CPU::if_decimal() const {
    return (registers.P >> 3) & 0x1;
}


bool CPU::if_break() const {
    return (registers.P >> 4) & 0x1;
}


bool CPU::if_overflow() const {
    return (registers.P >> 6) & 0x1;
}


bool CPU::if_sign() const {
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


uint8_t CPU::pop() {
    return load(0x0100 + (++registers.SP));
}


void CPU::push(uint8_t data) {
    store(0x0100 + registers.SP--, data);
}


uint8_t CPU::load(uint16_t addr) const {
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
    return (next_byte() + registers.X) % 256;
}


uint16_t CPU::get_ZPY() {
    return (next_byte() + registers.Y) % 256;
}


uint16_t CPU::get_IN() {
    uint16_t low = little_to_big_endian(next_byte(), next_byte());
    uint16_t high = little_to_big_endian(next_byte(), next_byte()) + 1;
    return ((uint16_t)load(high) << 8) + load(low);

}


uint16_t CPU::get_INX() {
    uint16_t zeroL = (next_byte() + registers.X) % 256;
    uint16_t zeroH = (zeroL + 1) % 256;
    return little_to_big_endian(load(zeroL), load(zeroH));
}


uint16_t CPU::get_INY() {
    uint16_t zeroL = next_byte();
    uint16_t zeroH = (zeroL + 1) % 256;
    return little_to_big_endian(load(zeroL), load(zeroH)) + registers.Y;
}


uint16_t CPU::get_REL() {
    // TODO: Chance this is wrong, didn't really get the conversion to signed and back
    return registers.PC + (int8_t)next_byte();
}


void CPU::ADC(uint16_t src) {
    uint8_t data = memory[src];
    uint16_t temp = data + registers.A + if_carry();
    set_zero(temp & 0xff);  // Review: What is meant by this? - This is not valid in decimal mode
    if (if_decimal()) {
        if (((registers.A & 0xf) + (data & 0xf) + if_carry()) > 9)
            temp += 6;
        set_sign(temp);
        set_overflow(!((registers.A ^ data) & 0x80) && ((registers.A ^ temp) & 0x80));
        set_carry(temp > 0x99);
    } else {
        set_sign(temp);
        set_overflow(!((registers.A ^ data) & 0x80) && ((registers.A ^ temp) & 0x80));
        set_carry(temp > 0x99);
    }
    registers.A = (uint8_t)temp;
}


void CPU::AND(uint16_t src) {
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


void CPU::ASL_ACC() {
    uint8_t data = registers.A;
    set_carry(data & 0x80);
    data <<= 1;
    data &= 0xff;
    set_sign(data);
    set_zero(data);
    registers.A = data;
}


void CPU::BCC(uint16_t src) {
    if (!if_carry()) {
        // TOOD: clk?
        registers.PC = src;
    }
}


void CPU::BCS(uint16_t src) {
    if (if_carry()) {
        // TOOD: clk?
        registers.PC = src;
    }
}


void CPU::BEQ(uint16_t src) {
    if (if_zero()) {
        // TOOD: clk?
        registers.PC = src;
    }
}


void CPU::BIT(uint16_t src) {
    uint8_t data = memory[src];
    set_sign(data);
    set_overflow(0x40 & data);  // Copy bit 6 to OVERFLOW flag
    set_zero(src & registers.A);
}


void CPU::BMI(uint16_t src) {
    if (if_sign()) {
        // TOOD: clk?
        registers.PC = src;
    }
}


void CPU::BNE(uint16_t src) {
    if (!if_zero()) {
        // TOOD: clk?
        registers.PC = src;
    }
}


void CPU::BPL(uint16_t src) {
    if (!if_sign()) {
        // TOOD: clk?
        registers.PC = src;
    }
}


void CPU::BRK() {
    ++registers.PC;
    push((registers.PC >> 8) & 0xff);   // Push return addr onto the stack
    push(registers.PC & 0xff);
    set_break(1);                       // Set Break flag before pushing
    push(registers.P);
    set_interrupt(1);
    registers.PC = (load(0xfffe) | (load(0xffff) << 8));
    // TODO: Didn't really understand break instruction
}


void CPU::BVC(uint16_t src) {
    if (!if_overflow()) {
        // TOOD: clk?
        registers.PC = src;
    }
}


void CPU::BVS(uint16_t src) {
    if (if_overflow()) {
        // TOOD: clk?
        registers.PC = src;
    }
}


void CPU::CLC() {
    set_carry(0);
}


void CPU::CLD() {
    set_decimal(0);
}


void CPU::CLI() {
    set_interrupt(0);
}


void CPU::CLV() {
    set_overflow(0);
}


void CPU::CMP(uint16_t src) {
    uint8_t data = memory[src];
    data = registers.A - data;
    set_carry(data < 0x100);
    set_sign(data);
    set_zero(data &= 0xff);
}


void CPU::CPX(uint16_t src) {
    uint8_t data = memory[src];
    data = registers.X - data;
    set_carry(data < 0x100);
    set_sign(data);
    set_zero(data &= 0xff);
}


void CPU::CPY(uint16_t src) {
    uint8_t data = memory[src];
    data = registers.Y - data;
    set_carry(data < 0x100);
    set_sign(data);
    set_zero(data &= 0xff);
}


void CPU::DEC(uint16_t src) {
    uint8_t data = memory[src];
    data = (data - 1) & 0xff;
    set_sign(data);
    set_zero(data);
    store(src, data);
}


void CPU::DEX() {
    uint8_t data = registers.X;
    data = (data - 1) & 0xff;
    set_sign(data);
    set_zero(data);
    registers.X = data;
}


void CPU::DEY() {
    uint8_t data = registers.Y;
    data = (data - 1) & 0xff;
    set_sign(data);
    set_zero(data);
    registers.Y = data;
}


void CPU::EOR(uint16_t src) {
    uint8_t data = memory[src];
    data ^= registers.A;
    set_sign(data);
    set_zero(data);
    registers.A = data;
}


void CPU::INC(uint16_t src) {
    uint8_t data = memory[src];
    data = (data + 1) & 0xff;
    set_sign(data);
    set_zero(data);
    store(src, data);
}


void CPU::INX() {
    uint8_t data = registers.X;
    data = (data + 1) & 0xff;
    set_sign(data);
    set_zero(data);
    registers.X = data;
}


void CPU::INY() {
    uint8_t data = registers.Y;
    data = (data + 1) & 0xff;
    set_sign(data);
    set_zero(data);
    registers.Y = data;
}


void CPU::JMP(uint16_t src) {
    // TODO: data of src address will be 8 bits, but PC is 16 bits
    uint8_t data = memory[src];
    registers.PC = data;
}


void CPU::JSR(uint16_t src) {
    uint8_t data = memory[src];
    --registers.PC;
    push((registers.PC >> 8) & 0xff);   // Push return addr onto the stack
    push(registers.PC & 0xff);
    registers.PC = data;
}


void CPU::LDA(uint16_t src) {
    uint8_t data = memory[src];
    set_sign(data);
    set_zero(data);
    registers.A = data;
}


void CPU::LDX(uint16_t src) {
    uint8_t data = memory[src];
    set_sign(data);
    set_zero(data);
    registers.X = data;
}


void CPU::LDY(uint16_t src) {
    uint8_t data = memory[src];
    set_sign(data);
    set_zero(data);
    registers.Y = data;
}


void CPU::LSR(uint16_t src) {
    uint8_t data = memory[src];
    set_carry(data & 0x80);
    data >>= 1;
    set_sign(data);
    set_zero(data);
    store(src, data);
}


void CPU::LSR_ACC() {
    uint8_t data = registers.A;
    set_carry(data & 0x80);
    data >>= 1;
    set_sign(data);
    set_zero(data);
    registers.A = data;
}


void CPU::NOP() {
    // no operation
}


void CPU::ORA(uint16_t src) {
    uint8_t data = memory[src];
    data |= registers.A;
    set_sign(data);
    set_zero(data);
    registers.A = data;
}


void CPU::PHA() {
    push(registers.A);
}


void CPU::PHP() {
    push(registers.P);
}


void CPU::PLA() {
    registers.A = pop();
    set_sign(registers.A);
    set_zero(registers.A);
}


void CPU::PLP() {
    registers.P = pop();
}


void CPU::ROL(uint16_t src) {
    uint16_t data = memory[src];
    data <<= 1;
    if (if_carry())
        data |= 0x1;
    set_carry(data > 0xff);
    data &= 0xff;
    set_sign(data);
    set_zero(data);
    store(src, data);
}


void CPU::ROL_ACC() {
    uint8_t data = registers.A;
    data <<= 1;
    if (if_carry())
        data |= 0x1;
    set_carry(data > 0xff);
    data &= 0xff;
    set_sign(data);
    set_zero(data);
    registers.A = data;
}


void CPU::ROR(uint16_t src) {
    uint8_t data = memory[src];
    if (if_carry())
        data |= 0x100;
    set_carry(data & 0x01);
    data >>= 1;
    set_sign(data);
    set_zero(data);
    store(src, data);
}


void CPU::ROR_ACC() {
    uint8_t data = registers.A;
    if (if_carry())
        data |= 0x100;
    set_carry(data & 0x01);
    data >>= 1;
    set_sign(data);
    set_zero(data);
    registers.A = data;
}


void CPU::RTI() {
    uint8_t data = pop();   // TODO: Seems to me like this needs to be uint16_t
    registers.P = data;
    data = pop();
    data |= (pop() << 8);   // TODO: Load return address from stack
    registers.PC = data;
}


void CPU::RTS() {
    uint8_t data = pop();       // TODO: Seems to me like this needs to be uint16_t
    data += (pop() << 8) + 1;   // TODO: Load return address from stack and add 1
    registers.PC = data;
}


void CPU::SBC(uint16_t src) {
    uint8_t data = memory[src];
    uint16_t temp = registers.A - data - if_carry();
    set_sign(temp);
    set_zero(temp & 0xff);      // TODO: Sign and Zero are invalid in decimal mode
    set_overflow(((registers.A ^ temp) & 0x80) && ((registers.A ^ data) & 0x80));
    if (if_decimal()) {
        if (((registers.A & 0xf) - if_carry()) < (data & 0xf))   // TODO: EP
            temp -= 6;
        if (temp > 0x99)
            temp -= 0x60;
    }
    set_carry(temp < 0x100);
    registers.A = (temp & 0xff);
}


void CPU::SEC() {
    set_carry(1);
}


void CPU::SED() {
    set_decimal(1);
}


void CPU::SEI() {
    set_interrupt(1);
}


void CPU::STA(uint16_t src) {
    store(src, registers.A);
}


void CPU::STX(uint16_t src) {
    store(src, registers.X);
}


void CPU::STY(uint16_t src) {
    store(src, registers.Y);
}


void CPU::TAX() {
    uint8_t data = registers.A;
    set_sign(data);
    set_zero(data);
    registers.X = data;
}


void CPU::TAY() {
    uint8_t data = registers.A;
    set_sign(data);
    set_zero(data);
    registers.Y = data;
}


void CPU::TSX() {
    uint8_t data = registers.SP;
    set_sign(data);
    set_zero(data);
    registers.X = data;
}


void CPU::TXA() {
    uint8_t data = registers.X;
    set_sign(data);
    set_zero(data);
    registers.A = data;
}


void CPU::TXS() {
    registers.SP = registers.X;
}


void CPU::TYA() {
    uint8_t data = registers.Y;
    set_sign(data);
    set_zero(data);
    registers.A = data;
}
