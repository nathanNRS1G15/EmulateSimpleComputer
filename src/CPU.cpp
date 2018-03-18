/*
 * CPU.cpp
 *
 *  Created on: Mar 17, 2018
 *      Author: NRS1G15
 */

#include "CPU.h"

class CPU::ALU {
protected:
	void add(signed int sourceReg) {
		AC = AC + sourceReg;
	}
	void sub(signed int sourceReg) {
		AC = AC - sourceReg;
	}
	void mul(signed int sourceReg) {
		AC = AC * sourceReg;
	}
	void div(signed int sourceReg) {
		AC = AC / sourceReg;
	}
};

class CPU::decoder {
public:
	unsigned char decodeOpcode(unsigned short instruction) {
		return instruction >> 12;
	}
	unsigned char decodeSourceReg(unsigned short instruction) {
		return (instruction >> 6) & 63;
	}
	unsigned char decodeTargetReg(unsigned short instruction) {
		return instruction & 63;
	}

};

void CPU::fetch(unsigned int address) {
	*IR = memory->load(address);
}

void CPU::execute(void) {
	unsigned char test = decoder->decodeOpcode(*IR);
}

