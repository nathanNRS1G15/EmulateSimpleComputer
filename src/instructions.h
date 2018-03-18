/*
 * instructions.h
 *
 *  Created on: Mar 17, 2018
 *      Author: NRS1G15
 */

#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

unsigned short instruction;		//16 bit instruction width for opcodes and references
/*
 * STRUCTURE OF INSTRUCTION
 * [4 bit opcode] [6 bit operand reference (source)] [6 bit operand reference (target)]
 */
const unsigned char lw(1);		//load word, for loading data, opcode 1
const unsigned char sw(2);		//store word, for storing data, opcode 2
const unsigned char add(3);		//add, for adding a source register to AC, opcode 3
const unsigned char sub(4);		//sub, for subtracting AC by a source register, opcode 4
const unsigned char multiply(5);//multiply, for multiply AC by a source register, opcode 5
const unsigned char divide(6);	//divide, for dividing AC by a source register, opcode 6
const unsigned char beq(7);		//branch if AC and source register are equal
const unsigned char bne(8);		//branch if AC and source register are not equal
const unsigned char slt(9);		//set if source register is less than AC
const unsigned char j(10);		//jump to certain point in code



#endif /* INSTRUCTIONS_H_ */
