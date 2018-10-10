/* 
* SR04.cpp
*
* Created: 2018-10-10 오후 4:27:08
* Author: usuzin
*/

#define F_CPU 16000000UL
#include "SR04.h"
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

// default constructor
SR04::SR04()
{
	SR04_init();
} //SR04

// default destructor
SR04::~SR04()
{
} //~SR04

void SR04::SR04_init(void)
{
	DDRG |= ( 1<<PORTG4 ); //0001 0000 트리거 출력 설정
	DDRG &= ( 1<<PORTG3 ); //1111 0111 에코 입력
	//DDRG |= 0x10; //0001 0000트리거 출력 설정
	//DDRG &= 0xF7; //1111 0111 에코 입력
	
	TCCR0 |= (1<<CS02) | (0<<CS01) | (0<<CS00); //64분주
	TCCR1B |= (1<<CS12) |  (0<<CS10);
	TIMSK |= (1<< TOIE0);
}

unsigned int SR04::measure_distance(void)
{
	//트리거 핀으로 펄스 출력
	PORTG &= ~(1 << PORTG4);	//Low 출력
	_delay_us(1);
	PORTG |= (1 << PORTG4);	//High 출력
	_delay_us(10);		//10us 대기
	PORTG &= ~(1 << PORTG4);	//Low 출력
	
	//에코 핀이 High가 될 때까지 대기
	TCNT1 = 0;
	while(!(PING & 0x08))
	{
		if(TCNT1 > 65000)
		{
			return 0;
		}
	}
	
	//에코 핀이 Low가 될 때까지 대기
	TCNT1 = 0;
	while(PING & 0x08) //0000 0100
	{
		if(TCNT1  > 650000) //측정불가능
		{
			TCNT1 = 0;
			break;
		}
	}
	
	//에코 핀의 펄스폭을 마이크로초 단위로 계산
	double pulse_width = 1000000.0 * TCNT1 * PRESCALER / F_CPU;
	
	return pulse_width / 58;	//cm 단위 변환
}
