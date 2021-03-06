/*
 * instructions.h
 *
 *  Created on: Mar 17, 2018
 *      Author: nrs1g15
 */

#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#define OPCODE 6				//Size of opcode in bits
#define OPERANDONE 13			//Size of operand one in bits
#define OPERANDTWO 13			//Size of operand two in bits
#define INSTRUCTIONSTART 1028	//Location of program instructions starting location in memory

/*
 * STRUCTURE OF INSTRUCTION
 * [6 bit opcode] [13 bit operand][13 bit operand]
 *
 * Table of instructions
 *[	lm	][	memory address	][				] 	*(load memory) 				Takes the value from memory address and places it in the AC register
 *[	li	][	immediate		][				]	*(load immediate)			Loads AC with immediate value
 *[	sm	][	memory address	][				]	*(save AC to memory)		Takes the value from the AC register and stores it in the memory address
 *[	si	][	memory address	][	immediate	]	*(save immediated)			Takes immediate value and saves it in memory
 *[	spdl][	memory address 	][				]	*(save to pre-defined		Takes AC and saves it to a memory address specified by another memory location
 *												  location)
 *[	lpdl][	memory address	][				]	*(load from pre-defined		Takes AC and loads corresponding memory address value into AC
 *												  location)
 *[	add	][	memory address	][				]	*(add) 						Adds together current value in AC and value from memory address
 *[	addi][	immediate		][				]	*(add immediate)			Adds together current value in AC and immediate value
 *[	sub	][	memory address	][				]	*(sub)						Subtracts value in memory address from AC value
 *[	subi][	immediate		][				]	*(sub immediate)			Subtracts immediate value from AC value
 *[	mul	][	memory address	][				]	*(multiply)					Multiplies together current value in AC and value from memory address
 *[	muli][	immediate		][				]	*(multiply immediate)		Multiplies together current value in AC and immediate value
 *[	di	][	memory address	][				]	*(divide)					Divides current value in AC by value from memory address
 *[	divi][	immediate		][				]	*(divide immediate)			Divides AC value by immediate value
 *[	beq	][	memory address	][	PC offset	]	*(branch if equal)			Offsets PC counter by PC offset amount if AC and memory address values are equal
 *[	beqi][	immediate		][	PC offset	]	*(branch if equal imm)		Offsets PC counter by PC offset amount if AC and immediate values are equal
 *[	bne	][	memory address	][	PC offset	]	*(branch if not equal)		Offsets PC counter by PC offset amount if AC and memory address values are not equal
 *[	bnei][	immediate		][	PC offset	]	*(branch if n equal imm)	Offsets PC counter by PC offset amount if AC and immediate values are not equal
 *[	slt	][	memory address	][				]	*(set on less than)			Sets AC to 1 if memory address value is less than AC value
 *[	slti][	immediate		][				]	*(set on less than imm)		Sets AC to 1 if immediate value is less than AC value
 *[	j	][					][	PC offset	]	*(jump)						Offset the PC counter by PC offset amount
 *
 */

//Corresponding values for each opcode
#define LM 		0x01
#define LI		0x02
#define SM 		0x03
#define SI		0x04
#define SPDL	0x05
#define LPDL	0x06
#define ADD 	0x07
#define ADDI 	0x08
#define SUB 	0x09
#define SUBI 	0x0a
#define MUL 	0x0b
#define MULI 	0x0c
#define DIV 	0x0d
#define DIVI 	0x0e
#define BEQ 	0x0f
#define BEQI 	0x10
#define BNE 	0x11
#define BNEI 	0x12
#define SLT		0x13
#define SLTI	0x14
#define J		0x15

#endif /* INSTRUCTIONS_H_ */
