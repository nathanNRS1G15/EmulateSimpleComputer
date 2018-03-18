/*
 * memory.cpp
 *
 *  Created on: Mar 18, 2018
 *      Author: NRS1G15
 */

#include "memory.h"

void memory::save(signed int sourceValue, unsigned int targetAddress) {
	memoryAddress[targetAddress] = sourceValue;
}
signed int memory::load(unsigned int targetAddress){
	return memoryAddress[targetAddress];
}
