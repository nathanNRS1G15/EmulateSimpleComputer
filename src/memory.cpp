/*
 * memory.cpp
 *
 *  Created on: Mar 18, 2018
 *      Author: NRS1G15
 */


#include "memory.h"

void memory::save(signed int sourceValue, signed int targetAddress) {
#if DEBUGMODE
	memoryBlock[targetAddress] = sourceValue;
	memoryLog('S', targetAddress, sourceValue);
#else
	memoryBlock[targetAddress] = sourceValue;
#endif
}

signed int memory::load(unsigned int targetAddress) {
#if DEBUGMODE
	signed int output = memoryBlock[targetAddress];
	memoryLog('S', targetAddress, output);
	return output;
#else
	return memoryBlock[targetAddress];
#endif
}
