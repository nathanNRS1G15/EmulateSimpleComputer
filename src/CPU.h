/*
 * CPU.h
 *
 *  Created on: Mar 18, 2018
 *      Author: Sil
 */

#ifndef CPU_H_
#define CPU_H_

#include "debug.h"

#include "instructions.h"
#include "memory.h"

class CPU {
public:
	void fetch(unsigned int address);
	void execute(void);
	memory *memory;

protected:
	signed int IRreg = 0;	//IR register, unsigned as all instructions are positive
	signed int *IR = &IRreg;
	signed int ACreg = 0;	//AC register, signed as calculations could have negative numbers
	signed int *AC = &ACreg;
	unsigned int PRreg = 0;	//PC register, unsigned as locations will be positive
	unsigned int *PR = &PRreg;

	class ALU;
	class decoder;
	ALU *ALU;
	decoder *decoder;
};




#endif /* CPU_H_ */
