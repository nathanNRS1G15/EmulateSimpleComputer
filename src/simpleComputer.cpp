/*
 * simpleComputer.cpp
 *
 *  Created on: Mar 17, 2018
 *      Author: NRS1G15
 */

#include "simpleComputer.h"
#include <cstdlib>

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
		ALULog("sub", source, temp, *AC);
	}
	void mul(signed int source, signed int *AC) {
		signed int temp = *AC;
		*AC = *AC * source;
		ALULog("mul", source, temp, *AC);
	}
	void div(signed int source, signed int *AC) {
		signed int temp = *AC;
		*AC = *AC / source;
		ALULog("div", source, temp, *AC);
	}
	void slt(signed int source, signed int *AC) {
		signed int temp = *AC;
		*AC = (source < temp) ? 1 : 0;
		ALULog("slt", source, temp, *AC);
	}
	void PR(signed int increment, signed int *PR) {
		signed int temp = *PR;
		*PR = *PR + increment;
		ALULog("PR", increment, temp, *PR);
	}
#else
	void add(signed int source, signed int *target) {
		*target = *target + source;
	}
	void sub(signed int source, signed int *target) {
		*target = *target - source;
	}
	void mul(signed int source, signed int *target) {
		*target = *target * source;
	}
	void div(signed int source, signed int *target) {
		*target = *target / source;
	}
	void slt(signed int source, signed int *target) {
		*target = (source < *target) ? 1 : 0;
	}
	void PR(signed int increment, signed int *PR) {
		*PR = *PR + increment;
	}
#endif

};

class simpleComputer::decoder {
public:
#if DEBUGMODE
	unsigned char decodeOPCode(unsigned int instruction) {
		unsigned char result = (instruction >> (OPERANDONE + OPERANDTWO));
		instructionDecodeLog("OPCode", instruction, result);
		return result;
	}
	unsigned short decodeOperandOne(unsigned int instruction) {
		unsigned short result = (instruction >> OPERANDONE) & 0x1fff;
		instructionDecodeLog("Operand one", instruction, result);
		return result;
	}
	signed short decodeOperandTwo(unsigned short instruction) {
		signed short result = (((instruction & 0x1fff) >> 12) == 1) ? ((instruction & 0x1fff) | 0xe000) : (instruction & 0x1fff);
		instructionDecodeLog("Operand two", instruction, result);
		return result;
	}
#else
	unsigned char decodeOPCode(unsigned int instruction) {
		return (instruction >> (OPERANCEONE + OPERANCETWO));
	}
	unsigned short decodeOperandOne(unsigned int instruction) {
		return (instruction >> OPERANDONE) & 0x1fff;
	}
	signed short decodeOperandTwo(unsigned short instruction) {
		return instruction & 0x1fff;
	}
#endif
};

class simpleComputer::memory {
public:
	void save(int address, int value) {
#if DEBUGMODE
		memoryBlock[address] = value;
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
	*IR = memory->load(*PR);
#endif

	execute();
}

void simpleComputer::execute(void) {
#if DEBUGMODE
	unsigned char opCode = decoder->decodeOPCode(*IR);
	CPULog('E', opCode, "na");
	switch(opCode) {
	case LM:
		*AC = memory->load(decoder->decodeOperandOne(*IR));
		ALU->PR(1, PR);
		CPULog('R', *AC, "AC");
		break;
	case LI:
		*AC = decoder->decodeOperandOne(*IR);
		ALU->PR(1, PR);
		CPULog('R', *AC, "AC");
		break;
#else
	switch(decoder->decodeOPRode(*IR)) {
	case LM:
		*AC = memory->load(decoder->decodeOperandOne(*IR));
		ALU->PR(1, PR);
		break;
	case LI:
		*AC = decoder->decodeOperandOne(*IR);
		ALU->PR(1, PR);
		break;
#endif
	case SM:
		memory->save(decoder->decodeOperandOne(*IR), decoder->decodeOperandTwo(*IR));
		ALU->PR(1, PR);
		break;
	case SI:
		memory->save(decoder->decodeOperandOne(*IR), *AC);
		ALU->PR(1, PR);
		break;
	case ADD:
		ALU->add(memory->load(decoder->decodeOperandOne(*IR)), AC);
		ALU->PR(1, PR);
		break;
	case ADDI:
		ALU->add(decoder->decodeOperandOne(*IR), AC);
		ALU->PR(1, PR);
		break;
	case SUB:
		ALU->sub(memory->load(decoder->decodeOperandOne(*IR)), AC);
		ALU->PR(1, PR);
		break;
	case SUBI:
		ALU->sub(decoder->decodeOperandOne(*IR), AC);
		ALU->PR(1, PR);
		break;
	case MUL:
		ALU->mul(memory->load(decoder->decodeOperandOne(*IR)), AC);
		ALU->PR(1, PR);
		break;
	case MULI:
		ALU->mul(decoder->decodeOperandOne(*IR), AC);
		ALU->PR(1, PR);
		break;
	case DIV:
		ALU->div(memory->load(decoder->decodeOperandOne(*IR)), AC);
		ALU->PR(1, PR);
		break;
	case DIVI:
		ALU->div(decoder->decodeOperandOne(*IR), AC);
		ALU->PR(1, PR);
		break;
	case BEQ:
		ALU->sub(memory->load(decoder->decodeOperandOne(*IR)), AC);
		!AC ? ALU->PR(decoder->decodeOperandTwo(*IR), PR) : ALU->PR(1, PR);
		break;
	case BEQI:
		ALU->sub(decoder->decodeOperandOne(*IR), AC);
		!AC ? ALU->PR(decoder->decodeOperandTwo(*IR), PR) : ALU->PR(1, PR);
		break;
	case BNE:
		ALU->sub(memory->load(decoder->decodeOperandOne(*IR)), AC);
		!AC ? ALU->PR(1, PR) : ALU->PR(decoder->decodeOperandTwo(*IR), PR);
		break;
	case BNEI:
		ALU->sub(decoder->decodeOperandOne(*IR), AC);
		!AC ? ALU->PR(1, PR) : ALU->PR(decoder->decodeOperandTwo(*IR), PR);
		break;
	case SLT:
		ALU->slt(memory->load(decoder->decodeOperandOne(*IR)), AC);
		break;
	case SLTI:
		ALU->slt(decoder->decodeOperandOne(*IR), AC);
		break;
	case J:
			ALU->PR(decoder->decodeOperandTwo(*IR), PR);
		break;
	default:
		exit(0);
		break;
	}
	fetch();
}

void simpleComputer::flashMemory(signed int *array, signed int size) {
	for(int i = 100; i < size + 100; i++) {
		memory->save(i, array[i - 100]);
	}
	fetch();
}
