/*
 * Stack.h
 *
 *  Created on: 21.04.2020
 *      Author: marce
 */

#ifndef SRC_RFM95_STACK_H_
#define SRC_RFM95_STACK_H_

#include "stm32l4xx_hal.h"

#define STACK_SIZE			255

class Stack {
public:
	Stack();

	void initStack();
	void push(uint8_t data);
	uint8_t pop(void);
	bool isEmpty(void);
	bool isFull(void);
	uint8_t getSize(void);

private:
	uint8_t size;
	uint8_t data[STACK_SIZE];


};

#endif /* SRC_RFM95_STACK_H_ */
