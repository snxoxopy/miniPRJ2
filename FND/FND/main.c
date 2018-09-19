/*
 * FND.c
 *
 * Created: 2018-09-14 오후 2:25:49
 * Author : usuzin
 */ 
#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "FND.h"

void TimerInterruptInit(void);

volatile uint8_t timercounter0 = 0;
volatile unsigned int FndValue = 0;
 
ISR(TIMER0_OVF_vect)
{
	if(timercounter0%4 == 0) 
		displayFND(0, FndValue%10);  // 1의 자리
	else if(timercounter0%4 == 1) 
		displayFND(1, FndValue%100/10);  // 10의 자리
	else if(timercounter0%4 == 2) 
		displayFND(2, FndValue%1000/100);  // 100의 자리
	else if(timercounter0%4 == 3) 
		displayFND(3, FndValue/1000);  // 1000의 자리
		
	timercounter0++;
	if (timercounter0 >= 200)
	{
		timercounter0 = 0;
	}
}

int main(void)
{
	FND_init();
	TimerInterruptInit();
	sei();
	
    while (1) 
    {
		_delay_ms(100);
		_delay_ms(100);
		FndValue++;
    }
}

void TimerInterruptInit(void)
{
	TCCR0 |= (1<<CS02) | (0<<CS01) | (0<<CS00);
	TIMSK |= (1<<TOIE0);
}
