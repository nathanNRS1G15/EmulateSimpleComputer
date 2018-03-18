/*
 * memory.cpp
 *
 *  Created on: Mar 18, 2018
 *      Author: NRS1G15
 */


#include "memory.h"

void memory::save(signed int sourceValue, unsigned int targetAddress) {
#if DEBUGMODE == true
	memoryAddress[targetAddress] = sourceValue;
	memoryLog("Save", targetAddress, sourceValue);
#else
	memoryAddress[targetAddress] = sourceValue;
#endif
}

signed int memory::load(unsigned int targetAddress){
#if DEBUGMODE == true
	signed int output = memoryAddress[targetAddress];
	memoryLog("Load", targetAddress, output);
	return output;
#else
	return memoryAddress[targetAddress];
#endif
}
