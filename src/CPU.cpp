/*
 * CPU.cpp
 *
 *  Created on: Mar 17, 2018
 *      Author: NRS1G15
 */

#include "CPU.h"

class CPU::ALU {
public:
#if DEBUGMODE == true
	void add(signed int source, signed int *AC) {
		signed int temp = *AC;
		*AC = *AC + source;
		ALULog("add", source, signed int temp, signed int *AC) {
	}
	void sub(signed int source, signed int *AC) {
		signed int temp = *AC;
		*AC = *AC - source;
		ALULog("add", source, signed int temp, signed int *AC) {
	}
	void mul(signed int source, signed int *AC) {
		signed int temp = *AC;
		*AC = *AC * source;
		ALULog("add", source, signed int temp, signed int *AC) {
	}
	void div(signed int source, signed int *AC) {
		signed int temp = *AC;
		*AC = *AC / source;
		ALULog("add", source, signed int temp, signed int *AC) {
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
#if DEBUGMODE == true
	unsigned char decodeOpcode(unsigned int instruction) {
		unsigned char result = instruction >> 24;
		decoderLog("Opcode", instruction, result);
		return result;
	}
	unsigned short decodeAddress(unsigned int instruction) {
		unsigned short = (instruction >> 8) & 0xffff;
		decoderLog("Opcode", instruction, result);
		return result;
	}
	signed short decodeImmediate(unsigned int instruction) {
		signed short = (instruction >> 8) & 0xffff;
		decoderLog("Opcode", instruction, result);
		return result;
	}
	signed char decodeOffSet(unsigned short instruction) {
		signed char = instruction;
		decoderLog("Opcode", instruction, result);
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
#if DEBUGMODE == true
	signed int input = memory->load(address);
	CPULog("Fetch", input);
	return input;
#else
	*IR = memory->load(address);
#endif
}

void CPU::execute(void) {
#if DEBUGMODE == true
	unsigned char opcode = decoder->decodeOpcode(*IR);
	CPULog("Execute", opcode);
	switch(opcode) {
#else
	switch(decoder->decodeOpcode(*IR)) {
#endif
	case lw:
		*AC = memory->load(decoder->decodeAddress(instruction));
		break;
	case sw:
		memory->save(*AC, decoder->decodeAddress(instruction));
		break;
	case add:
		ALU->add(decoder->decodeAddress(instruction), AC);
		break;
	case addi:
		ALU->add(decoder->decodeImmediate(instruction), AC);
		break;
	case sub:
		ALU->sub(decoder->decodeAddress(instruction), AC);
		break;
	case subi:
		ALU->sub(decoder->decodeImmediate(instruction), AC);
		break;
	case mul:
		ALU->mul(decoder->decodeAddress(instruction), AC);
		break;
	case muli:
		ALU->mul(decoder->decodeImmediate(instruction), AC);
		break;
	case div:
		ALU->div(decoder->decodeAddress(instruction), AC);
		break;
	case divi:
		ALU->div(decoder->decodeImmediate(instruction), AC);
		break;
	}
}

