#include <iostream>
#include "../include/CPU.h"

int main() {
	std::ifstream ROM;
	ROM.open("../nestest/nestest.nes", std::ios::binary);

	


	CPU cpu = CPU(0xC000);	// TODO: initial PC from reset vectors
	cpu.power_on();


	return 0;
}