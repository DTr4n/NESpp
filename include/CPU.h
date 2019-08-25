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
    uint8_t pop();
    void push(uint8_t data);

    // Load a byte from the memory address
    uint8_t load(uint16_t addr) const; // TODO: Not complete

    // Store a byte to the memory address
    void store(uint16_t addr, uint8_t data); // TODO: Not complete

    void next_byte(); // TODO: I feel like this can be replaced with load(pc++)

    inline uint16_t little_to_big_endian(uint8_t low, uint8_t high);

    // Addressing Modes
    uint16_t get_IMM();     // Immediate
    uint16_t get_AB();      // Absolute
    uint16_t get_ABX();     // Absolute Indexed X
    uint16_t get_ABY();     // Absolute Indexed Y
    uint16_t get_ZP();      // Zero-Page
    uint16_t get_ZPX();     // Zero-Page Indexed X
    uint16_t get_ZPY();     // Zero-Page Indexed Y
    uint16_t get_ACC();     // TODO: Accumulator might not even be needed
    uint16_t get_IN();      // Indirect
    uint16_t get_INX();     // Indexed Indirect
    uint16_t get_INY();     // Indirect Indexed
    uint16_t get_REL();     // Relative

    // Opcodes
    // TODO: some of these codes, I have been using a temp variable supporting only 8 bits, but need to extend to 16 bits
    void ADC(uint16_t src);         // Add memory to accumulator with carry
    void AND(uint16_t src);         // "AND" memory with accumulator
    void ASL(uint16_t src);         // Shift left one bit (memory)
    void ASL_ACC(uint16_t src);     // Shift left one bit (accumulator)
 
    void BCC(uint16_t src);         // Branch on carry clear
    void BCS(uint16_t src);         // Branch on carry set
    void BEQ(uint16_t src);         // Branch on result zero
    void BIT(uint16_t src);         // Test bits in memory with accumulator
    void BMI(uint16_t src);         // Branch on result minus
    void BNE(uint16_t src);         // Branch on result not zero
    void BPL(uint16_t src);         // Branch on result plus
    void BRK(uint16_t src);         // Force break
    void BVC(uint16_t src);         // Branch on overflow clear
    void BVS(uint16_t src);         // Branch on overflow set

    void CLC(uint16_t src);         // Clear carry flag
    void CLD(uint16_t src);         // Clear decimal mode
    void CLI(uint16_t src);         // Clear interrupt disable bit
    void CLV(uint16_t src);         // Clear overflow flag
    void CMP(uint16_t src);         // Compare memory and accumulator
    void CPX(uint16_t src);         // Compare memory and index X
    void CPY(uint16_t src);         // Compare memory and index Y

    void DEC(uint16_t src);         // Decrement memory by one
    void DEX(uint16_t src);         // Decrement index X by one
    void DEY(uint16_t src);         // Decrement index Y by one

    void EOR(uint16_t src);         // "XOR" memory with accumulator

    void INC(uint16_t src);         // Increment memory by one
    void INX(uint16_t src);         // Increment index X by one
    void INY(uint16_t src);         // Increment index Y by one

    void JMP(uint16_t src);         // Jump to new location
    void JSR(uint16_t src);         // Jump to new location saving return address

    void LDA(uint16_t src);         // Load accumulator with memory
    void LDX(uint16_t src);         // Load index X with memory
    void LDY(uint16_t src);         // Load index Y with memory
    void LSR(uint16_t src);         // Shift right one bit (memory)
    void LSR_ACC(uint16_t src);     // Shift right one bit (accumulator)

    void NOP(uint16_t src);         // No operation

    void ORA(uint16_t src);         // "OR" memory with accumulator

    void PHA(uint16_t src);         // Push accumulator on stack
    void PHP(uint16_t src);         // Push processor status on stack
    void PLA(uint16_t src);         // Pull accumulator from stack
    void PLP(uint16_t src);         // Pull processor status from stack

    void ROL(uint16_t src);         // Rotate one bit left (memory)
    void ROL_ACC(uint16_t src);     // Rotate one bit left (accumulator)
    void ROR(uint16_t src);         // Rotate one bit right (memory)
    void ROR_ACC(uint16_t src);     // Rotate one bit right (accumulator)
    void RTI(uint16_t src);         // Return from interrupt
    void RTS(uint16_t src);         // Return from subroutine

    void SBC(uint16_t src);         // Subtract memory from accumulator with borrow
    void SEC();                     // Set carry flag
    void SED();                     // Set decimal mode
    void SEI();                     // Set interrupt disable status
    void STA(uint16_t src);         // Store accumulator in memory
    void STX(uint16_t src);         // Store index X in memory
    void STY(uint16_t src);         // Store index Y in memory

    void TAX();                     // Transfer accumulator to index X
    void TAY();                     // Transfer accumulator to index Y
    void TSX();                     // Transfer stack pointer to index X
    void TXA();                     // Transfer index X to accumulator
    void TXS();                     // Transfer index X to stack pointer
    void TYA();                     // Transfer index Y to accumulator
};

#endif // CPU_H
