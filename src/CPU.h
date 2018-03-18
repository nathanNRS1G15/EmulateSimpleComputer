/*
 * CPU.h
 *
 *  Created on: Mar 18, 2018
 *      Author: Sil
 */

#ifndef CPU_H_
#define CPU_H_

#if DEBUGMODE
	#include "debug.h"
#endif

#include "instructions.h"
#include "memory.h"

class CPU {
public:
	void fetch(unsigned int address);
	void execute(void);

protected:
	static signed int IRreg;	//IR register, unsigned as all instructions are positive
	signed int *IR = &IRreg;
	static signed int ACreg;	//AC register, signed as calculations could have negative numbers
	signed int *AC = &ACreg;
	static unsigned int PRreg;	//PC register, unsigned as locations will be positive
	unsigned int *PR = &PRreg;

	class ALU;
	class decoder;
	ALU *ALU;
	decoder *decoder;
	memory *memory;
};




#endif /* CPU_H_ */
