/*
 * instructions.h
 *
 *  Created on: Mar 17, 2018
 *      Author: NRS1G15
 */

#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

unsigned short instruction;		//32 bit instruction width for opcodes and references
/*
 * STRUCTURE OF INSTRUCTION
 * [8 bit opcode] [16 bit operand][8 bit operand]
 *
 * Table of instructions
 *[	lw	][	memory address	][				] 	*(load word) 			Takes the value from memory address and places it in the AC register
 *[	sw	][	memory address	][				]	*(save word)			Takes the value from the AC register and stores it in the memory address
 *[	add	][	memory address	][				]	*(add) 					Adds together current value in AC and value from memory address
 *[	addi][	immediate		][				]	*(add immediate)		Adds together current value in AC and immediate value
 *[	sub	][	memory address	][				]	*(sub)					Subtracts value in memory address from AC value
 *[	subi][	immediate		][				]	*(sub immediate)		Subtracts immediate value from AC value
 *[	mul	][	memory address	][				]	*(multiply)				Multiplies together current value in AC and value from memory address
 *[	muli][	immediate		][				]	*(multiply immediate)	Multiplies together current value in AC and immediate value
 *[	div	][	memory address	][				]	*(divide)				Divides current value in AC by value from memory address
 *[	divi][	immediate		][				]	*(divide immediate)		Divides AC value by immediate value
 *[	beq	][	memory address	][	PC offset	]	*(branch if equal)		Offsets PC counter by PC offset amount if AC and memory address values are equal
 *[	beqi][	immediate		][	PC offset	]	*(branch if equal imm)	Offsets PC counter by PC offset amount if AC and immediate values are equal
 *[	bne	][	memory address	][	PC offset	]	*(branch if not equal)	Offsets PC counter by PC offset amount if AC and memory address values are not equal
 *[	bnei][	immediate		][	PC offset	]	*(branch if n equal imm)Offsets PC counter by PC offset amount if AC and immediate values are not equal
 *[	slt	][	memory address	][				]	*(set on less than)		Sets AC to 1 if memory address value is less than AC value
 *[	slti][	immediate		][				]	*(set on less than imm)	Sets AC to 1 if immediate value is less than AC value
 *[	j	][					][	PC offset	]	*(jump)					Offset the PC counter by PC offset amount
 *
 */
const unsigned char lw	(1);
const unsigned char sw	(2);
const unsigned char add	(3);
const unsigned char addi(4);
const unsigned char sub	(5);
const unsigned char subi(6);
const unsigned char mul	(7);
const unsigned char muli(8);
const unsigned char div	(9);
const unsigned char divi(10);
const unsigned char beq	(11);
const unsigned char beqi(12);
const unsigned char bne	(13);
const unsigned char bnei(14);
const unsigned char slt	(15);
const unsigned char slti(16);
const unsigned char j	(17);



#endif /* INSTRUCTIONS_H_ */
