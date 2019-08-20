#ifndef CPU_H
#define CPU_H

#include <cstdint>

class CPU {
public:
    CPU();
    ~CPU();

    // uint8_t fetch();
    // void execute();


private:
    struct CPU_Registers {
        uint8_t A;      // Accumulator
        uint8_t X;      // X Index
        uint8_t Y;      // Y Index
        uint16_t PC;    // Program Counter
        uint8_t S;      // Stack Pointer
        uint8_t P;      // Status Register
    };

    CPU_Registers registers;
    uint8_t memory[65536];

    // TODO clock; 
    
    // Status register accessors and mutators
    bool if_carry() const;
    bool if_zero() const;
    void if_interrupt() const;
    void if_decimal() const; 
    void if_break() const;
    bool if_overflow() const;
    bool if_sign() const;
    void set_carry(bool condition);
    void set_zero(uint8_t src);
    void set_interrupt(bool condition);
    void set_decimal(bool condition);
    void set_break(bool condition);
    void set_overflow(bool condition);
    void set_sign(uint8_t src);

    uint16_t rel_addr(uint8_t src); // TODO: Not complete
    // void set_status_register();
    // uint8_t get_status_register();
    // uint8_t pull();
    // void push(uint8_t);

    // Load a byte from the memory address
    uint8_t load(uint16_t addr) const; // TODO: Not complete

    // Store a byte to the memory address
    void store(uint16_t addr, uint8_t data); // TODO: Not complete

    void next_byte(); // TODO: Not complete

    inline uint16_t little_to_big_endian(uint8_t low, uint8_t high);

    // ----------------------
    // Instructions Operation
    // ----------------------
    // Addressing Modes Acronyms : 
    //      IMM - Immediate
    //      AB  - Absolute
    //      ABX - Absolute Indexed X
    //      ABY - Absolute Indexed Y
    //      ZP  - Zero-Page
    //      ZPX - Zero-Page Indexed X
    //      ZPY - Zero-Page Indexed Y
    //      ACC - Accumulator
    //      IN  - Indirect
    //      INX - Indirect Indexed X
    //      INY - Indirect Indexed Y
    //      REL - Relative

    // ADC - add memory to accumulator with carry
    void ADC_IMM();
    void ADC_ZP();
    void ADC_ZPX();
    void ADC_AB();
    void ADC_ABX();
    void ADC_ABY();
    void ADC_INX();
    void ADC_INY();
    void ADC_helper(uint8_t src);

    // AND - "AND" memory with accumulator
    void AND_IMM();
    void AND_ZP();
    void AND_ZPX();
    void AND_AB();
    void AND_ABX();
    void AND_ABY();
    void AND_INX();
    void AND_INY();
    void AND_helper(uint8_t src);

    // ASL - shift left one bit (memory or accumulator)
    void ASL_ACC();
    void ASL_ZP();
    void ASL_ZPX();
    void ASL_AB();
    void ASL_ABX();
    uint8_t ASL_helper(uint8_t src);

    // BCC - branch on carry clear
    void BCC_REL();

    // BCS - branch on carry set
    void BCS_REL();

    // BEQ - branch on result zero
    void BEQ_REL();

    // BIT - test bits in memory with accumulator
    void BIT_ZP();
    void BIT_AB();

    // BNE - branch on result not zero
    void BMI_REL();

    // BPL - branch on result plus
    void BNE_REL();

    // BRK - force break
    void BPL_REL();

    // BVC - branch on overflow clear
    void BVC_REL();

    // BVS - branch on overflow set
    void BVS_REL();

    // CLC - clear carry flag
    void CLC();

    // CLD - clear decimal mode
    void CLD();

    // CLI - clear interrupt disable bit
    void CLI();

    // CLV - clear overflow flag
    void CLV();

    // CMP - compare memory and accumulator
    void CMP_IMM();
    void CMP_ZP();
    void CMP_ZPX();
    void CMP_AB();
    void CMP_ABX();
    void CMP_ABY();
    void CMP_INX();
    void CMP_INY();

    // CPX - compare memory and index X
    void CPX_IMM();
    void CPX_ZP();
    void CPX_AB();

    // CPY - compare memory and index Y
    void CPY_IMM();
    void CPY_ZP();
    void CPY_AB();

    // DEC - decrement memory by one
    void DEC_ZP();
    void DEC_ZPX();
    void DEC_AB();
    void DEC_ABX();

    // DEX - decrement index X by one
    void DEX();

    // DEY - decrement index Y by one
    void DEY();

    // EOR - "XOR" memory with accumulator
    void EOR_IMM();
    void EOR_ZP();
    void EOR_ZPX();
    void EOR_AB();
    void EOR_ABX();
    void EOR_ABY();
    void EOR_INX();
    void EOR_INY();

    // INC - increment memory by one
    void INC_ZP();
    void INC_ZPX();
    void INC_AB();
    void INC_ABX();

    // INX - increment index X by one
    void INX();

    // INY - increment index Y by one
    void INY();

    // JMP - jump to new location
    void JMP_AB();
    void JMP_IN();

    // JSR - jump to new location saving return address
    void JSR_AB();

    // LDA - load accumulator with memory
    void LDA_IMM();
    void LDA_ZP();
    void LDA_ZPX();
    void LDA_AB();
    void LDA_ABX();
    void LDA_ABY();
    void LDA_INX();
    void LDA_INY();

    // LDX - load index X with memory
    void LDX_IMM();
    void LDX_ZP();
    void LDX_ZPY();
    void LDX_AB();
    void LDX_ABY();

    // LDY - load index Y with memory
    void LDY_IMM();
    void LDY_ZP();
    void LDY_ZPX();
    void LDY_AB();
    void LDY_ABX();

    // LSR - shift right one bit (memory or accumulator)
    void LSR_ACC();
    void LSR_ZP();
    void LSR_ZPX();
    void LSR_AB();
    void LSR_ABX();

    // NOP - no operation
    void NOP();

    // ORA - "OR" memory with accumulator
    void ORA_IMM();
    void ORA_ZP();
    void ORA_ZPX();
    void ORA_AB();
    void ORA_ABX();
    void ORA_ABY();
    void ORA_INX();
    void ORA_INY();

    // PHA - push accumulator on stack
    void PHA();

    // PHP - push processor status on stack
    void PHP();

    // PLA - pull accumulator from stack
    void PLA();

    // PLP - pull processor status from stack
    void PLP();

    // ROL - rotate one bit left (memory or accumulator)
    void ROL_ACC();
    void ROL_ZP();
    void ROL_ZPX();
    void ROL_AB();
    void ROL_ABX();

    // ROR - rotate one bit right (memory or accumulator)
    void ROR_ACC();
    void ROR_ZP();
    void ROR_ZPX();
    void ROR_AB();
    void ROR_ABX();

    // RTI - return from interrupt
    void RTI();

    // RTS - return from subroutine
    void RTS();

    // SBC - subtract memory from accumulator with borrow
    void SBC_IMM();
    void SBC_ZP();
    void SBC_ZPX();
    void SBC_AB();
    void SBC_ABX();
    void SBC_ABY();
    void SBC_INX();
    void SBC_INY();

    // SEC - set carry flag
    void SEC();

    // SED - set decimal mode
    void SED();

    // SEI - set interrupt disable status
    void SEI();

    // STA - store accumulator in memory
    void STA_ZP();
    void STA_ZPX();
    void STA_AB();
    void STA_ABX();
    void STA_ABY();
    void STA_INX();
    void STA_INY();

    // STX - store index X in memory
    void STX_ZP();
    void STX_ZPY();
    void STX_AB();

    // STY - store index Y in memory
    void STY_ZP();
    void STY_ZPX();
    void STY_AB();

    // TAX - transfer accumulator to index X
    void TAX();

    // TAY - transfer accumulator to index Y
    void TAY();

    // TSX - transfer stack pointer to index X
    void TSX();

    // TXA - transfer index X to accumulator
    void TXA();

    // TXS - transfer index X to stack pointer
    void TXS();

    // TYA - transfer index Y to accumulator
    void TYA();

};

#endif // CPU_H
