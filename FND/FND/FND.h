/*
 * FND.h
 *
 * Created: 2018-09-14 오후 4:56:46
 *  Author: kccistc
 */ 


#ifndef FND_H_
#define FND_H_

#include <avr/io.h>

#define FND_DATA_DDR		DDRC   // FND Data Port
#define FND_CONTROL_DDR		DDRF   // FND Control Port
#define FND_DATA_PORT		PORTC   // FND Data Port
#define FND_CONTROL_PORT	PORTF   // FND Control Port


void FND_init(void);
void displayFND(uint8_t position, uint8_t number);
void displayNumber(int count);

#endif /* FND_H_ */