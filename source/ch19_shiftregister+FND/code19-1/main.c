/*
 * code19-1.c p430
 *
 * Created: 2018-09-19 오후 2:30:52
 * Author : usuzin
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

/*
//'bit'위치의 비트를 1 또는 0으로 설정하기 위한 매크로함수
#define set_bit(bit)	(PORTE |= _BV(bit))
#define clear_bit(bit)	(PORTE &= ~_BV(bit))


#define SHIFT_CLOCK	0
#define LATCH_CLOCK 1
#define DATA		2*/

// ATmega128 포트 E에 연결 된 위치
#define Data_pin	0
#define Latchpin	1
#define Clockpin	2

#if 0
void ShiftClock(void)
{
	set_bit(SHIFT_CLOCK);		//이동 클록을 HIGH
	clear_bit(SHIFT_CLOCK);		//이동 클록을 LOW
}

void LatchClock(void)
{
	set_bit(LATCH_CLOCK);
	clear_bit(LATCH_CLOCK);
}
#endif

void FND_init(void)
{
	DDRE = 0xff;   // FND Data Port
}

/*
void displayFND(uint8_t position, uint8_t number)
{
	//					0   1     2     3     4     5     6     7     8     9
	uint8_t num[] =	{0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67};
	// FND 위치				1000,  100,   10,    1
	uint8_t fndselect[] = {0x80, 0x40, 0x20, 0x10};
	
	FND_CONTROL_PORT = FND_CONTROL_PORT|0xf0;
	FND_CONTROL_PORT &= ~fndselect[position];
	FND_DATA_PORT = num[number];
}*/



int main(void)
{
	uint8_t Data_val[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67};
	uint8_t Data_buff;
	PORTE = 0x00;
	FND_init();
	while(1)
	{
		
	
	//입력데이터: 레지스터에 들어가는 숫자에 해당하는 LED 밝기 제어 비트
	for(int i = 0; i<8; i++)
	{
		Data_buff = (Data_val[3] << i);	//i번째 비트 확인 (shift)
		
		if(Data_buff & 0x80) //입력 데이터의 가장 상위비트가 1일 경우
		{
			PORTE |= (1 << Data_pin);	//해당 data pin을 set(High)
		}
		else
		{
			PORTE &= ~(1 << Data_pin);	//해당 data pin을 LOW
		}
		//CLK pin
		//L
		PORTE &= ~(1 << Clockpin); 
		//H
		PORTE |= (1 << Clockpin);
		//L
		PORTE &= ~(1 << Clockpin);
	}
	
	//Latch
	//L
		PORTE &= ~(1 << Latchpin);
	//H
		PORTE |= (1 << Latchpin);
	//L
		PORTE &= ~(1 << Latchpin);
   /* while (1) 
    {
    }*/
	}
}

