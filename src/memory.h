/*
 * memory.h
 *
 *  Created on: Mar 18, 2018
 *      Author: Sil
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#if DEBUGMODE
	#include "debug.h"
#endif

class memory {
public:
	void save(signed int sourceValue, unsigned int targetAddress);
	signed int load(unsigned int targetAddress);

protected:
	signed int memoryBlock[1023] = {0}; 			//1024 32 bits memory locations of shared data
	signed int* memoryAddress = &memoryBlock[0];	//pointer set to to memoryBlock so it can be accessed from any where correctly
};

#endif /* MEMORY_H_ */
