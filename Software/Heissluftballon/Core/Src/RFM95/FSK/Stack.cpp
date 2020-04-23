/*
 * Stack.cpp
 *
 *  Created on: 21.04.2020
 *      Author: marce
 */

#include "Stack.h"

Stack::Stack() {
	// TODO Auto-generated constructor stub

}


void Stack::initStack(){
	for(int i = 0; i<STACK_SIZE;i++){
		this->data[i] = 0;
	}
}
void Stack::push(uint8_t data){
	if(size < STACK_SIZE){
		this->data[size] = data;
		size++;
	}
}

uint8_t Stack::pop(void){
	if(size > 0){
		size--;
		return this->data[size];
	}
	return 0;
}

bool Stack::isEmpty(void){
	return (size == 0 ? true : false);
}

bool Stack::isFull(void){
	return (size == STACK_SIZE ? true : false);
}

uint8_t Stack::getSize(void){
	return size;
}
