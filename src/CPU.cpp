/*
 * CPU.cpp
 *
 *  Created on: Mar 17, 2018
 *      Author: NRS1G15
 */

#include "CPU.h"

class CPU::ALU {
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

class CPU::decoder {
public:
#if DEBUGMODE
	unsigned char decodeOpcode(unsigned int instruction) {
		unsigned char result = instruction >> 24;
		instructionDecodeLog("Opcode", instruction, result);
		return result;
	}
	unsigned short decodeAddress(unsigned int instruction) {
		unsigned short result = (instruction >> 8) & 0xffff;
		instructionDecodeLog("Opcode", instruction, result);
		return result;
	}
	signed short decodeImmediate(unsigned int instruction) {
		signed short result = (instruction >> 8) & 0xffff;
		instructionDecodeLog("Opcode", instruction, result);
		return result;
	}
	signed char decodeOffSet(unsigned short instruction) {
		signed char result = instruction;
		instructionDecodeLog("Opcode", instruction, result);
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

void CPU::fetch(unsigned int address) {
#if DEBUGMODE
	signed int input = memory->load(address);
	CPULog("Fetch", input);
	*IR = memory->load(input);
#else
	*IR = memory->load(address);
#endif
}

void CPU::execute(void) {
#if DEBUGMODE
	unsigned char opcode = decoder->decodeOpcode(*IR);
	CPULog("Execute", opcode);
	switch(opcode) {
#else
	switch(decoder->decodeOpcode(*IR)) {
#endif
	case LW:
		*AC = memory->load(decoder->decodeAddress(*IR));
		break;
	case SW:
		memory->save(*AC, decoder->decodeAddress(*IR));
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

