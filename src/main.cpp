#include <iostream>
#include "../include/CPU.h"

int main() {
	CPU cpu = CPU(0xC000);	// TODO: initial PC from reset vectors
	cpu.power_on();

	std::cout << "Done" << std::endl;
	return 0;
}