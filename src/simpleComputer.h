/*
 * CPU.h
 *
 *  Created on: Mar 18, 2018
 *      Author: Sil
 */

#ifndef SIMPLECOMPUTER_H_
#define SIMPLECOMPUTER_H_

#include "debug.h"
#include <array>
#include "instructions.h"

class simpleComputer {
public:
	void startCPU(void) { fetch();	}
	void flashMemory(signed int *array, signed int size);
	signed int readMem(signed int address);

protected:
	void fetch(void);
	void execute(void);
	signed int IRreg = 0;	//IR register, unsigned as all instructions are positive
	signed int *IR = &IRreg;
	signed int ACreg = 0;	//AC register, signed as calculations could have negative numbers
	signed int *AC = &ACreg;
	signed int PRreg = INSTRUCTIONSTART;	//PC register, unsigned as locations will be positive
	signed int *PR = &PRreg;

	class ALU {
	public:
		void add(signed int source, signed int *AC);
		void sub(signed int source, signed int *AC);
		void mul(signed int source, signed int *AC);
		void div(signed int source, signed int *AC);
		void slt(signed int source, signed int *AC);
		void PR(signed int increment, signed int *PR);
	};
	class decoder {
	public:
		unsigned char decodeOPCode(unsigned int instruction);
		unsigned short decodeOperandOne(unsigned int instruction);
		signed short decodeOperandTwo(unsigned short instruction);
	};
	class memory {
	public:
		void save(int address, int value);
		signed int load(int address);
		void output(signed int value) {
			cout << value << endl;
		}

		static signed int memoryBlock[1024];
	};

	memory *memory;
	ALU *ALU;
	decoder *decoder;
};




#endif /* SIMPLECOMPUTER_H_ */
