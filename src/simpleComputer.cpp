/*
 * simpleComputer.cpp
 *
 *  Created on: Mar 17, 2018
 *      Author: NRS1G15
 */

#include "simpleComputer.h"
#include <cstdlib>

#if DEBUGMODE		//Checks to see if DEBUGMODE is set, if so the following compiles which include calls to debug.h
	void simpleComputer::ALU::add(signed int source, signed int *AC) {
		signed int temp = *AC;				//Saves current state of the AC register
		*AC = *AC + source;					//Adds source value to the AC then writes result to AC
		ALULog("add", source, temp, *AC);	//Logs ALU in add mode, source value, original AC value and result from addition
	}
	void simpleComputer::ALU::sub(signed int source, signed int *AC) {
		signed int temp = *AC;
		*AC = *AC - source;					//Subtracts source value from AC value
		ALULog("sub", source, temp, *AC);	//Logs operation
	}
	void simpleComputer::ALU::mul(signed int source, signed int *AC) {
		signed int temp = *AC;
		*AC = *AC * source;
		ALULog("mul", source, temp, *AC);
	}
	void simpleComputer::ALU::div(signed int source, signed int *AC) {
		signed int temp = *AC;
		*AC = *AC / source;
		ALULog("div", source, temp, *AC);
	}
	void simpleComputer::ALU::slt(signed int source, signed int *AC) {
		signed int temp = *AC;
		*AC = (source < temp) ? 1 : 0;		//Detects if source is smaller than AC, if so sets AC to 1 or else sets AC to 0
		ALULog("slt", source, temp, *AC);
	}
	void simpleComputer::ALU::PR(signed int increment, signed int *PR) {
		signed int temp = *PR;
		*PR = *PR + increment;				//Increments PR by increment amount
		ALULog("PR", increment, temp, *PR);
	}
#else			//If DEBUGMODE is not set the following code compiles. Same functionality as above but debug code removed
	void simpleComputer::ALU::add(signed int source, signed int *AC) {
		*AC = *AC + source;
	}
	void simpleComputer::ALU::sub(signed int source, signed int *AC) {
		*AC = *AC - source;
	}
	void simpleComputer::ALU::mul(signed int source, signed int *AC) {
		*AC = *AC * source;
	}
	void simpleComputer::ALU::div(signed int source, signed int *AC) {
		*AC = *AC / source;
	}
	void simpleComputer::ALU::slt(signed int source, signed int *AC) {
		*AC = (source < *AC) ? 1 : 0;
	}
	void simpleComputer::ALU::PR(signed int increment, signed int *PR) {
		*PR = *PR + increment;
	}
#endif

#if DEBUGMODE
	unsigned char simpleComputer::decoder::decodeOPCode(unsigned int instruction) {
		unsigned char result = (instruction >> (OPERANDONE + OPERANDTWO));				//Decodes opcode by shifting machine code by operand one plus operand two size.
		instructionDecodeLog("OPCode", instruction, result);							//Logs decoder in opcode mode, original instruction and result from shifting.
		return result;																	//Returns opcode result.
	}
	unsigned short simpleComputer::decoder::decodeOperandOne(unsigned int instruction) {
		/*
		 * Decodes operand one by shifting machine code by operand one size and removing leading 3 bits as they're part of opcode.
		 */
		unsigned short result = (instruction >> OPERANDONE) & 0x1fff;
		instructionDecodeLog("Operand one", instruction, result);
		return result;
	}
	signed short simpleComputer::decoder::decodeOperandTwo(unsigned short instruction) {
		/* Decodes operand two by first detecting if its a signed number, by testing the 13th bit as thats the leading bit of operand two.
		 * Then if its signed it removes leading 3 bits and replaces them with 3 1s to give it signed status on a short,
		 * otherwise it just removes leading 3 bits. */
		signed short result = (((instruction & 0x1fff) >> 12) == 1) ? ((instruction & 0x1fff) | 0xe000) : (instruction & 0x1fff);
		instructionDecodeLog("Operand two", instruction, result);
		return result;
	}
#else
	unsigned char simpleComputer::decoder::decodeOPCode(unsigned int instruction) {
		return (instruction >> (OPERANDONE + OPERANDTWO));
	}
	unsigned short simpleComputer::decoder::decodeOperandOne(unsigned int instruction) {
		return (instruction >> OPERANDONE) & 0x1fff;
	}
	signed short simpleComputer::decoder::decodeOperandTwo(unsigned short instruction) {
		return (((instruction & 0x1fff) >> 12) == 1) ? ((instruction & 0x1fff) | 0xe000) : (instruction & 0x1fff);
	}
#endif

#if DEBUGMODE
	void simpleComputer::memory::save(signed int address, signed int value) {
		if(address > MEMORYSIZE)			//Detects if the address sent is larger than the available memory size,
			output(value);					//if so it outputs the sent value to output (which prints value to.
		else
			memoryBlock[address] = value;	//Saves value to memory address location.
		memoryLog('S', address, value);		//Logs save mode, address and value.
	}
	signed int simpleComputer::memory::load(signed int address) {
		signed int result = memoryBlock[address];	//Saves the value from the memory at address location.
		memoryLog('L', address, result);
		return result;								//Returns the value from memory location.
	}
#else
	void simpleComputer::memory::save(signed int address, signed int value) {
		if(address > MEMORYSIZE)
			output(value);
		else
			memoryBlock[address] = value;
	}
	signed int simpleComputer::memory::load(signed int address) {
		return memoryBlock[address];
	}
#endif

signed int simpleComputer::memory::memoryBlock[MEMORYSIZE];	//Initializes memory array with size of memory size defined in instructions.h.

bool simpleComputer::fetch(void) {
#if DEBUGMODE
	signed int input = memory->load(*PR);	//Gets the instruction at memory location corresponding to value in PR.
	CPULog('F', input, "na");				//Logs Fetch mode, instruction gotten and "na" as last argument isnt needed for fetch log.
	*IR = input;							//Sets IR register to instruction.
#else
	*IR = memory->load(*PR);
#endif

	if(!(*IR))								//Detects if the instruction is 0, representing end of instructions/end of program.
		return true;						//Returns true to end CPU execution.
	else
		return execute();					//Starts execution on the instruction in IR.
}

bool simpleComputer::execute(void) {
	bool status = false;						//Sets status to false to show CPU is actively working instructions.
#if DEBUGMODE
	unsigned char opCode = decoder->decodeOPCode(*IR);	//Calls decoder to decode opcode from instruction in IR.
	CPULog('E', opCode, "na");					//Logs execution on decoded instruction.
	switch(opCode) {							//Switch dependent on what the decoded instruction was.
	case LM:									//LM case.
		*AC = memory->load(decoder->decodeOperandOne(*IR));	//Loads the value from memory location corresponding to decoded operand one into AC register.
		ALU->PR(1, PR);							//Increments the PR counter by 1 so next fetch the next instruction is fetched.
		CPULog('R', *AC, "AC");					//Logs current status of AC register after execution of opcode.
		break;
	case LI:
		*AC = decoder->decodeOperandOne(*IR);	//Due to immediate used the immediate is decoded from operand one and loaded into AC.
		ALU->PR(1, PR);
		CPULog('R', *AC, "AC");
		break;
	case LPDL:
		/*
		 * For LPDL and similar instructions; it decodes the memory location storing the wanted memory address from operand one, then gets the value from this decoded memory location,
		 * then loads the value from the corresponding memory address into AC. */
		*AC = memory->load(memory->load(decoder->decodeOperandOne(*IR)));
		ALU->PR(1, PR);
		CPULog('R', *AC, "AC");
		break;
#else
	switch(decoder->decodeOPCode(*IR)) {
	case LM:
		*AC = memory->load(decoder->decodeOperandOne(*IR));
		ALU->PR(1, PR);
		break;
	case LI:
		*AC = decoder->decodeOperandOne(*IR);
		ALU->PR(1, PR);
		break;
	case LPDL:
		*AC = memory->load(memory->load(decoder->decodeOperandOne(*IR)));
		ALU->PR(1, PR);
		break;
#endif
	case SI:
		/*
		 * For SI instruction; first it decodes the memory address from operand one, then decodes the value being saved from operand two.
		 * The memory address and value is then sent to the memory to be saved. */
		memory->save(decoder->decodeOperandOne(*IR), decoder->decodeOperandTwo(*IR));
		ALU->PR(1, PR);
		break;
	case SM:
		memory->save(decoder->decodeOperandOne(*IR), *AC);			//Saves AC value to memory address decoded from operand one.
		ALU->PR(1, PR);
		break;
	case SPDL:
		//For SPDL instruction; Saves AC value to memory address corresponding to value in memory location, at address decoded from operand one.
		memory->save(memory->load(decoder->decodeOperandOne(*IR)), *AC);
		ALU->PR(1, PR);
		break;
	case ADD:
		//Sends value at memory address corresponding to decoded operand one to ALU to be added, along with AC register pointer
		ALU->add(memory->load(decoder->decodeOperandOne(*IR)), AC);
		ALU->PR(1, PR);
		break;
	case ADDI:
		ALU->add(decoder->decodeOperandOne(*IR), AC);				//Sends decoded value from operand one to ALU to be subtracted, along with AC register pointer
		ALU->PR(1, PR);
		break;
	case SUB:
		//Sends value at memory address corresponding to decoded operand one to ALU to be subtracted, along with AC register pointer
		ALU->sub(memory->load(decoder->decodeOperandOne(*IR)), AC);
		ALU->PR(1, PR);
		break;
	case SUBI:
		ALU->sub(decoder->decodeOperandOne(*IR), AC);				//Sends decoded value from operand one to ALU to be added, along with AC register pointer
		ALU->PR(1, PR);
		break;
	case MUL:
		//Sends value at memory address corresponding to decoded operand one to ALU to be multiplied, along with AC register pointer
		ALU->mul(memory->load(decoder->decodeOperandOne(*IR)), AC);
		ALU->PR(1, PR);
		break;
	case MULI:
		ALU->mul(decoder->decodeOperandOne(*IR), AC);				//Sends decoded value from operand one to ALU to be multiplied, along with AC register pointer
		ALU->PR(1, PR);
		break;
	case DIV:
		//Sends value at memory address corresponding to decoded operand one to ALU to be divided, along with AC register pointer
		ALU->div(memory->load(decoder->decodeOperandOne(*IR)), AC);
		ALU->PR(1, PR);
		break;
	case DIVI:
		ALU->div(decoder->decodeOperandOne(*IR), AC);				//Sends decoded value from operand one to ALU to be divided, along with AC register pointer
		ALU->PR(1, PR);
		break;
	case BEQ:
		/*
		 * BEQ and BEQI start by subtracting AC by the wanted value. Then, depending on whether the result of this is zero or not,
		 * increments PR by the value stored in operand two, if numbers were equal, or increments PR by 1, if numbers weren't equal. */
		ALU->sub(memory->load(decoder->decodeOperandOne(*IR)), AC);
		(*AC == 0) ? ALU->PR(decoder->decodeOperandTwo(*IR), PR) : ALU->PR(1, PR);
		break;
	case BEQI:
		ALU->sub(decoder->decodeOperandOne(*IR), AC);
		(*AC == 0) ? ALU->PR(decoder->decodeOperandTwo(*IR), PR) : ALU->PR(1, PR);
		break;
	case BNE:
		/*
		 * BNE and BENI are similar to BEQ and BEQI except that if AC is zero, PR is incremented by 1 or if AC is not zero,
		 * increments PR by value stored in operand two.	*/
		ALU->sub(memory->load(decoder->decodeOperandOne(*IR)), AC);
		(*AC == 0) ? ALU->PR(1, PR) : ALU->PR(decoder->decodeOperandTwo(*IR), PR);
		break;
	case BNEI:
		ALU->sub(decoder->decodeOperandOne(*IR), AC);
		(*AC == 0) ? ALU->PR(1, PR) : ALU->PR(decoder->decodeOperandTwo(*IR), PR);
		break;
	case SLT:
		//Sends value at memory address corresponding to decoded operand one to ALU to be checked against AC, along with AC register pointer
		ALU->slt(memory->load(decoder->decodeOperandOne(*IR)), AC);
		ALU->PR(1, PR);
		break;
	case SLTI:
		ALU->slt(decoder->decodeOperandOne(*IR), AC);				//Sends decoded value from operand one to ALU to be divided, along with AC register pointer
		ALU->PR(1, PR);
		break;
	case J:
			ALU->PR(decoder->decodeOperandTwo(*IR), PR);			//Sends decoded value from operand one to ALU to be added to PR, along with PR register pointer
		break;
	default:
		status = true;		//If opcode decoded is none of the above, status is set to true to show end of program
		break;
	}
	return status;
}

void simpleComputer::flashMemory(signed int *array, signed int size) {
	for(int i = INSTRUCTIONSTART; i < size + INSTRUCTIONSTART; i++) {	//Loops through machine code array
		memory->save(i, array[i - INSTRUCTIONSTART]);					//Saves machine code to corresponding memory location
	}
}

signed int simpleComputer::readMem(signed int address) {
	return memory->load(address);
}
