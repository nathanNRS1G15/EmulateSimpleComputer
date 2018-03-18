/*
 * memory.h
 *
 *  Created on: Mar 18, 2018
 *      Author: Sil
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include "debug.h"
#include <stdlib.h>

class memory {
public:
	void save(signed int sourceValue, signed int targetAddress);
	signed int load(unsigned int targetAddress);

protected:
	signed int memoryBlock[10] = {0};
};

#endif /* MEMORY_H_ */
