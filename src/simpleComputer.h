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
#include <vector>
using namespace std;

#define MEMORYSIZE 2048			//Total size of memory

class simpleComputer {			//Class that encapsulates the different processor parts
protected:
	bool fetch(void);			//Fetches machine code at current PR location and places it in IR
	bool execute(void);			//Decodes and executes the current instruction in IR
	signed int IR = 0;					//IR register used for storing instructions
	signed int AC = 0;					//AC register used for storing result of ALU
	signed int PR = INSTRUCTIONSTART;	//PC register used for keeping track of current point in program. Set to instruction start as thats were starting point it
	class ALU {				//ALU class to emulate an ALU within a CPU
	public:
		signed int add(signed int source, signed int AC);	//Adds a source value and current value in AC
		signed int sub(signed int source, signed int AC);	//Subtracts a source value and current value in AC
		signed int mul(signed int source, signed int AC);	//Multiplies a source value and current value in AC
		signed int div(signed int source, signed int AC);	//Divides a source value and current value in AC
		signed int slt(signed int source, signed int AC);	//Sets AC to 1 if source less than AC or 0 otherwise
		/*
		 * The following modifies PR based on increment value, or if a branch instruction the value of AC is tested
		 * so then PR is either incremented by 1 or the wanted increment value if branch condition was true.
		 */
		signed int PR(signed int increment, signed int AC, signed int PR, char mode);
	};
	class decoder {			//Decoder class to emulate a decoder within the CPU
	public:
		unsigned char decodeOPCode(unsigned int instruction);			//Returns opcode from machine code
		unsigned short decodeOperandOne(unsigned int instruction);		//Returns operand one from machine code
		signed short decodeOperandTwo(unsigned short instruction);		//Returns operand two from machine code
	};

	class systemBus {		//System bus class to emulate a system bus between CPU, memory and IO
	protected:
		class memory {		//Memory class to emulated memory
		public:
			void save(int address, int value);		//Allows saving of value to a memory address
			signed int load(int address);			//Allows loading of value from a memory address

		private:
			static signed int memoryBlock[MEMORYSIZE];	//Declaration of memory block
		};

		class IO {			//IO class to emulate IO
		public:
			void IOoutput(signed int address, signed int data);		//Outputs to console, which emulates an external device
		};

		memory memory;		//Instance of memory within systemBus class
		IO IO;				//Instance of IO within systemBus class

	public:
		void busWrite(signed int address, signed int data);	//Allows wring to system bus that sends the data to corresponding location
		signed int busRead(signed address);					//Allows reading from system bus that gets the data from corresponding location
	};

	systemBus systemBus;	//Creates instance of systemBus within simpleComputer class
	ALU ALU;				//Creates instance of ALU within simpleComputer class
	decoder decoder;		//Creates instance of decoder within simpleComputer class

public:
	bool startCPU(void) {		//Starting function for the emulator
		while (!(fetch()));		//Loops fetch until true is returned to indicate finished program execution
		return true;
	}

	void flashMemory(signed int *array, signed int size);		//Loads machine code into memory from the start of instructions address

};

#endif /* SIMPLECOMPUTER_H_ */
