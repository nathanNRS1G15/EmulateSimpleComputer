/*
 * instructions.h
 *
 *  Created on: Mar 17, 2018
 *      Author: NRS1G15
 */

#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#define OPCODE 8
#define OPERANDONE 16
#define OPERANDTWO 8

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
 *[	di	][	memory address	][				]	*(divide)				Divides current value in AC by value from memory address
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
#define LW 		0x01
#define SW 		0x02
#define ADD 	0x03
#define ADDI 	0x04
#define SUB 	0x05
#define SUBI 	0x06
#define MUL 	0x07
#define MULI 	0x08
#define DIV 	0x09
#define DIVI 	0x0a
#define BEQ 	0x0b
#define BEQI 	0x0c
#define BNE 	0x0d
#define BNEI 	0x0e
#define SLT		0x0f
#define SLTI	0x10
#define J		0x11



#endif /* INSTRUCTIONS_H_ */
