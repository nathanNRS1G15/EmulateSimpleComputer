/*
 * CPU.h
 *
 *  Created on: Mar 18, 2018
 *      Author: nrs1g15
 */

#ifndef SIMPLECOMPUTER_H_
#define SIMPLECOMPUTER_H_

#include "debug.h"
#include "instructions.h"
#include <iostream>
using namespace std;

#define MEMORYSIZE 2048			//Total size of memory

class simpleComputer {			//Class that encapsulates the emulator
protected:
	bool fetch(void);			//Fetches machine code at current PR location and places it in IR
	bool execute(void);			//Decodes and executes the current instruction in IR
	signed int IRreg = 0;		//IR register used for storing instructions
	signed int *IR = &IRreg;	//IR register pointer to pass to out of scope functions to allow modifying of IR
	signed int ACreg = 0;		//AC register used for storing result of ALU
	signed int *AC = &ACreg;	//AC register pointer to pass to out of scope functions to allow modifying of AC
	signed int PRreg = INSTRUCTIONSTART;	//PC register used for keeping track of current point in program. Set to instruction start as thats were starting point it
	signed int *PR = &PRreg;	//PR register pointer to pass to out of scope functions to allow modifying of PR

	class ALU {
	public:
		void add(signed int source, signed int *AC);	//Adds a source value and current value in AC
		void sub(signed int source, signed int *AC);	//Subtracts a source value and current value in AC
		void mul(signed int source, signed int *AC);	//Multiplies a source value and current value in AC
		void div(signed int source, signed int *AC);	//Divides a source value and current value in AC
		void slt(signed int source, signed int *AC);	//Sets AC to 1 if source less than AC or 0 otherwise
		void PR(signed int increment, signed int *AC, signed int *PR, char mode);	//Modifies PR register based on increment value
	};
	class decoder {
	public:
		unsigned char decodeOPCode(unsigned int instruction);			//Returns opcode from machine code
		unsigned short decodeOperandOne(unsigned int instruction);		//Returns operand one from machine code
		signed short decodeOperandTwo(unsigned short instruction);		//Returns operand two from machine code
	};

	class systemBus {
	protected:
		class memory {
		public:
			void save(int address, int value);		//Allows saving of value to a memory address
			signed int load(int address);			//Allows loading of value from a memory address

		protected:
			static signed int memoryBlock[MEMORYSIZE];	//Declaration of memory block
		};

		class IO {
		public:
			void IOoutput(signed int address, signed int data);
		};

		memory *memory;		//Creates instance of memory within simpleComputer class
		IO *IO;

	public:
		void busWrite(signed int address, signed int data);
		signed int busRead(signed address);
	};

	systemBus *systemBus;
	ALU *ALU;			//Creates instance of ALU within simpleComputer class
	decoder *decoder;	//Creates instance of decoder within simpleComputer class

public:
	bool startCPU(void) {		//Starting function for the emulator
		while (!(fetch()));		//Loops fetch until true is returned to indicate finished program execution
		return true;
	}

	void flashMemory(signed int *array, signed int size);		//Loads machine code into memory from the start of instructions address

};

#endif /* SIMPLECOMPUTER_H_ */
