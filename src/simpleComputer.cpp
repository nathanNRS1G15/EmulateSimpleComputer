/*
 * simpleComputer.cpp
 *
 *  Created on: Mar 17, 2018
 *      Author: NRS1G15
 */

#include "simpleComputer.h"
#include <iostream>
#include <vector>

class simpleComputer::ALU {
public:
#if DEBUGMODE
	void add(signed int source, signed int *AC) {
		signed int temp = *AC;
		*AC = *AC + source;
		ALULog("add", source, temp, *AC);
	}
	void sub(signed int source, signed int *AC) {
		signed int temp = *AC;
		*AC = *AC - source;
		ALULog("add", source, temp, *AC);
	}
	void mul(signed int source, signed int *AC) {
		signed int temp = *AC;
		*AC = *AC * source;
		ALULog("add", source,  temp, *AC);
	}
	void div(signed int source, signed int *AC) {
		signed int temp = *AC;
		*AC = *AC / source;
		ALULog("add", source, temp, *AC);
	}
#else
	void add(signed int source, signed int *AC) {
		*AC = *AC + source;
	}
	void sub(signed int source, signed int *AC) {
		*AC = *AC - source;
	}
	void mul(signed int source, signed int *AC) {
		*AC = *AC * source;
	}
	void div(signed int source, signed int *AC) {
		*AC = *AC / source;
	}
#endif

};

class simpleComputer::decoder {
public:
#if DEBUGMODE
	unsigned char decodeOpcode(unsigned int instruction) {
		unsigned char result = instruction >> 24;
		instructionDecodeLog("Opcode", instruction, result);
		return result;
	}
	unsigned short decodeAddress(unsigned int instruction) {
		unsigned short result = (instruction >> 8) & 0xffff;
		instructionDecodeLog("Address", instruction, result);
		return result;
	}
	signed short decodeImmediate(unsigned int instruction) {
		signed short result = (instruction >> 8) & 0xffff;
		instructionDecodeLog("immediate", instruction, result);
		return result;
	}
	signed char decodeOffSet(unsigned short instruction) {
		signed char result = instruction;
		instructionDecodeLog("Offset", instruction, result);
		return result;
	}
#else
	unsigned char decodeOpcode(unsigned int instruction) {
		return instruction >> 24;
	}
	unsigned short decodeAddress(unsigned int instruction) {
		return (instruction >> 8) & 0xffff;
	}
	signed short decodeImmediate(unsigned int instruction) {
		return (instruction >> 8) & 0xffff;
	}
	signed char decodeOffSet(unsigned short instruction) {
		return instruction;
	}
#endif
};

class simpleComputer::memory {
public:
	void save(int address, int value) {
#if DEBUGMODE
		memoryBlock[address] = value;
		cout << memoryBlock[address] << endl;
		memoryLog('S', address, value);
#else
		memoryBlock[address] = value;
#endif
	}
	signed int load(int address) {
#if DEBUGMODE
		signed int result = memoryBlock[address];
		memoryLog('L', address, result);
		return result;
#else
		return memoryBlock[address];
#endif
	}

	static signed int memoryBlock[1024];
};
signed int simpleComputer::memory::memoryBlock[1024] = {0};

void simpleComputer::fetch(void) {
#if DEBUGMODE
	signed int input = memory->load(*PR);
	CPULog('F', input, "na");
	*IR = input;
#else
	*IR = memory->load(address);
#endif
}

void simpleComputer::execute(void) {
#if DEBUGMODE
	unsigned char opcode = decoder->decodeOpcode(*IR);
	CPULog('E', opcode, "na");
	switch(opcode) {
	case LW:
		*AC = memory->load(decoder->decodeAddress(*IR));
		CPULog('R', *AC, "AC");
		break;
	case LI:
		*AC = decoder->decodeImmediate(*IR);
		CPULog('R', *AC, "AC");
		break;
#else
	switch(decoder->decodeOpcode(*IR)) {
	case LW:
		*AC = memory->load(decoder->decodeAddress(*IR));
		break;
	case LI:
		*AC = decoder->decodeImmediate(*IR);
		break;
#endif
	case SW:
		memory->save(decoder->decodeAddress(*IR), *AC);
		break;
	case ADD:
		ALU->add(decoder->decodeAddress(*IR), AC);
		break;
	case ADDI:
		ALU->add(decoder->decodeImmediate(*IR), AC);
		break;
	case SUB:
		ALU->sub(decoder->decodeAddress(*IR), AC);
		break;
	case SUBI:
		ALU->sub(decoder->decodeImmediate(*IR), AC);
		break;
	case MUL:
		ALU->mul(decoder->decodeAddress(*IR), AC);
		break;
	case MULI:
		ALU->mul(decoder->decodeImmediate(*IR), AC);
		break;
	case DIV:
		ALU->div(decoder->decodeAddress(*IR), AC);
		break;
	case DIVI:
		ALU->div(decoder->decodeImmediate(*IR), AC);
		break;
	}
}

void simpleComputer::flashMemory(signed int *array, signed int size) {
	for(int i = 100; i < size + 100; i++) {
		memory->save(i, array[i - 100]);
	}
}
