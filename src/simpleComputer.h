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
	void fetch(void);
	void execute(void);
	void incrementPR(signed int increment);
	void flashMemory(signed int *array, signed int size);

protected:
	signed int IRreg = 0;	//IR register, unsigned as all instructions are positive
	signed int *IR = &IRreg;
	signed int ACreg = 0;	//AC register, signed as calculations could have negative numbers
	signed int *AC = &ACreg;
	unsigned int PRreg = 100;	//PC register, unsigned as locations will be positive
	unsigned int *PR = &PRreg;

	class ALU;
	class decoder;
	class memory;
	class IO;
	IO *IO;
	memory *memory;
	ALU *ALU;
	decoder *decoder;
};




#endif /* SIMPLECOMPUTER_H_ */
