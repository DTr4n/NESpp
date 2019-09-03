#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include <cstdio> // TODO: necessary? used for printf

class CPU {
public:

    CPU();
    // uint8_t fetch();
    void execute();


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

    /* Numeric value of opcode is used to index the function pointer table.
       Each entry of the table is a function emulating the corresponding opcode
    */
    // void (*Instruction_Set[256])(uint16_t src);
    /* TODO for long term maybe: Function pointer table alone won't work. Need to have 
       a struct that contains both function pointer to address type and opcode. And 
       then array of that struct
       http://www.multigesture.net/wp-content/uploads/mirror/zenogais/FunctionPointers.htm
    */


    // TODO clock; 
    
    // Status register accessors and mutators
    bool if_carry() const;
    bool if_zero() const;
    bool if_interrupt() const;
    bool if_decimal() const; 
    bool if_break() const;
    bool if_overflow() const;
    bool if_sign() const;
    void set_carry(bool condition);
    void set_zero(uint8_t src);
    void set_interrupt(bool condition);
    void set_decimal(bool condition);
    void set_break(bool condition);
    void set_overflow(bool condition);
    void set_sign(uint8_t src);

    // Read/Write 
    uint8_t pop();
    void push(uint8_t data);
    uint8_t load(uint16_t addr) const; // TODO: Not complete
    void store(uint16_t addr, uint8_t data); // TODO: Not complete
    uint8_t next_byte(); // TODO: I feel like this can be replaced with load(pc++)

    // Helper function to convert data from little endian to big endian
    inline uint16_t little_to_big_endian(uint8_t low, uint8_t high);

    // Addressing Modes
    uint16_t get_IMM();     // Immediate
    uint16_t get_AB();      // Absolute
    uint16_t get_ABX();     // Absolute Indexed X
    uint16_t get_ABY();     // Absolute Indexed Y
    uint16_t get_ZP();      // Zero-Page
    uint16_t get_ZPX();     // Zero-Page Indexed X
    uint16_t get_ZPY();     // Zero-Page Indexed Y
    uint16_t get_IN();      // Indirect
    uint16_t get_INX();     // Indexed Indirect
    uint16_t get_INY();     // Indirect Indexed
    uint16_t get_REL();     // Relative

    // Opcodes
    void ADC(uint16_t src);         // Add memory to accumulator with carry
    void AND(uint16_t src);         // "AND" memory with accumulator
    void ASL(uint16_t src);         // Shift left one bit (memory)
    void ASL_ACC();                 // Shift left one bit (accumulator)
 
    void BCC(uint16_t src);         // Branch on carry clear
    void BCS(uint16_t src);         // Branch on carry set
    void BEQ(uint16_t src);         // Branch on result zero
    void BIT(uint16_t src);         // Test bits in memory with accumulator
    void BMI(uint16_t src);         // Branch on result minus
    void BNE(uint16_t src);         // Branch on result not zero
    void BPL(uint16_t src);         // Branch on result plus
    void BRK();                     // Force break
    void BVC(uint16_t src);         // Branch on overflow clear
    void BVS(uint16_t src);         // Branch on overflow set

    void CLC();                     // Clear carry flag
    void CLD();                     // Clear decimal mode
    void CLI();                     // Clear interrupt disable bit
    void CLV();                     // Clear overflow flag
    void CMP(uint16_t src);         // Compare memory and accumulator
    void CPX(uint16_t src);         // Compare memory and index X
    void CPY(uint16_t src);         // Compare memory and index Y

    void DEC(uint16_t src);         // Decrement memory by one
    void DEX();                     // Decrement index X by one
    void DEY();                     // Decrement index Y by one

    void EOR(uint16_t src);         // "XOR" memory with accumulator

    void INC(uint16_t src);         // Increment memory by one
    void INX();                     // Increment index X by one
    void INY();                     // Increment index Y by one

    void JMP(uint16_t src);         // Jump to new location
    void JSR(uint16_t src);         // Jump to new location saving return address

    void LDA(uint16_t src);         // Load accumulator with memory
    void LDX(uint16_t src);         // Load index X with memory
    void LDY(uint16_t src);         // Load index Y with memory
    void LSR(uint16_t src);         // Shift right one bit (memory)
    void LSR_ACC();                 // Shift right one bit (accumulator)

    void NOP();                     // No operation

    void ORA(uint16_t src);         // "OR" memory with accumulator

    void PHA();                     // Push accumulator on stack
    void PHP();                     // Push processor status on stack
    void PLA();                     // Pull accumulator from stack
    void PLP();                     // Pull processor status from stack

    void ROL(uint16_t src);         // Rotate one bit left (memory)
    void ROL_ACC();                 // Rotate one bit left (accumulator)
    void ROR(uint16_t src);         // Rotate one bit right (memory)
    void ROR_ACC();                 // Rotate one bit right (accumulator)
    void RTI();                     // Return from interrupt
    void RTS();                     // Return from subroutine

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
