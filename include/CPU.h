#ifndef CPU_H
#define CPU_H

#include <cstdint>

class CPU {
private:
	struct CPU_Registers {
		uint8_t A;		// Accumulator
		uint8_t X;		// X Index
		uint8_t Y;		// Y Index
		uint16_t PC;	// Program Counter
		uint8_t S;		// Stack Pointer
		uint8_t P;		// Status Register
	};
    
    TODO clock; 
    
    bool if_carry();
    bool if_zero();
    void if_interrupt();
    void if_decimal(); 
    void if_break();
    bool if_overflow();
    bool if_sign();
    void set_carry(bool condition);
    void set_zero(uint8_t src);
    void set_interrupt(bool condition);
    void set_decimal(bool condition);
    void set_break(bool condition);
    void set_overflow(bool condition);
    void set_sign(uint8_t src);
    uint16_t rel_addr(uint8_t src);
    void set_status_register();
    uint8_t get_status_register();
    uint8_t pull();
    void push(uint8_t);
    uint8_t load();
    void store(uint8_t byte);
   
    // Addressing Modes
    uint16_t addr_immediate();
    uint16_t addr_absolute();
    uint8_t get_addr_zero-page();

    CPU_Registers registers;

    uint8_t fetch();
    void execute();

    void ADC(uint8_t operand);
    void ADC(uint16_t );
}

#endif // CPU_H
