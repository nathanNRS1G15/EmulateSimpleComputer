/*
 * CPU.h
 *
 *  Created on: Mar 17, 2018
 *      Author: NRS1G15
 */

#ifndef CPU_H_
#define CPU_H_

#include "memory.h"
//#include "instructions.h"

class CPU {
public:
	void fetch(unsigned int address);
	void execute(void);

protected:
	static signed int IRreg;	//IR register, unsigned as all instructions are positive
	signed int *IR = &IRreg;
	static signed int AC;		//AC register, signed as calculations could have negative numbers
	static unsigned int PR;	//PC register, unsigned as locations will be positive

	class ALU;
	class decoder;
	ALU *ALU;
	decoder *decoder;
	memory *memory;	//Declaration of memory for cpu to use
};


#endif /* CPU_H_ */
