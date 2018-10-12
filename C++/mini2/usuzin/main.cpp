/*
 * usuzin.cpp
 * 수동모드, LCD 센서 값 출력
 * Created: 2018-10-01 오후 4:38:14
 * Author : usuzin
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "motor.h"
#include "UART1.h"	//BT 통신을 위해 uart1사용
#include "I2C.h"	//LCD - AVR I2C 통신 이용
#include "I2C_LCD.h"
#include "SR04.h"

enum{GO=49, T_left, T_right, Stop, Back, Test};//ascii 1 2 3 4 5 6 

int sensor_chk =0;
void ADC_init(unsigned char channel);
int read_ADC(void);

ISR(TIMER1_OVF_vect)
{
	sensor_chk = !sensor_chk;
}

int main(void)
{
    UART1 uart;			//BT(uart1) 통신을 위한 클래스 선언
	motor mtr;			//모터 상태제어 클래스 선언
	I2C_LCD lcd;
	//SR04 sensor;
	
	int mtr_state;
	int mtr_v = 200;	//12ms 동안 high
	int rx_tag = 1;		//초기에 상태 설정 메세지 출력
	
	int read;
	float input_voltage;
	
	ADC_init(5);
	
	char buff[100];
	char buff2[100];
	char prt_state[100];
	unsigned int distance;

	//OCR1C = 0x7fff;	
	//TCCR1C |= ( (1<<CS12) | (1<<CS11) | (1<<CS10) );
	//TCCR1C |= (1<<CS32);
	//TCCR2 |= ( (1<<CS22) | (1<<CS21)| (1<<CS20));
	TIMSK |= (1<<TOIE1);
	//ETIMSK |= (1<<OCIE1C);

	
	sei();//uart 링버퍼 구현을 위한 전역적 인터럽트 실행
	
	lcd.I2C_LCD_clear();
	lcd.I2C_LCD_write_string_XY(0,0,"*USZ 0510*");
	
	while(1)
	{

		if(rx_tag)//rx가 들어오면
		{
			//상태 설정 메세지 uart
			uart.print_string("*********************************\r\n");
			uart.print_string("***********Motor_State.**********\r\n");
			uart.print_string("1. Go\r\n");
			uart.print_string("2. Right\r\n");
			uart.print_string("3. Left\r\n");
			uart.print_string("4. Stop\r\n");
			uart.print_string("Select Number>> \r\n");
			rx_tag = 0;
		}
		
		//모터 상태 읽어오기
		mtr_state = uart.mtr_chk();
		sprintf(buff,"State: %d \r\n", mtr_state);
		uart.print_string(buff);
		if(mtr_state)
		{
			sprintf(prt_state,"%s\r\n", ( (mtr_state == 49) ? "-> 1.GO" : (mtr_state == 50 ? "-> 2.Left" : (mtr_state == 51 ? "-> 3.Right" : (mtr_state == 52 ? "-> 4.Stop" : (mtr_state == 53 ? "-> 5.Back" : "") ) ) ) ) );
			//sprintf(buff,"State: %c \r\n", prt_state);
			uart.print_string(prt_state);
		}
		switch(mtr_state)
		{
			case GO:
				uart.print_string("Motor_GO\r\n");
				mtr.go(mtr_v);
				sprintf(buff,"%16s","GO");
				lcd.I2C_LCD_write_string_XY(1,0,buff);
				break;
				
			case T_left:
				uart.print_string("Motor_Left\r\n");	
				mtr.T_left(mtr_v);
				sprintf(buff,"%16s","Left");
				lcd.I2C_LCD_write_string_XY(1,0,buff);
				break;
				
			case T_right:
				uart.print_string("Motor_right\r\n");
				mtr.T_right(mtr_v);
				sprintf(buff,"%16s","Right");
				lcd.I2C_LCD_write_string_XY(1,0,buff);
				break;
					
			case Back:
				mtr.back(mtr_v);
				uart.print_string("Motor_back\r\n");
				sprintf(buff,"%16s","Back");
				lcd.I2C_LCD_write_string_XY(1,0,buff);
				break;
				
			case Stop:
				mtr.stop();
				sprintf(buff,"%16s","Stop");
				lcd.I2C_LCD_write_string_XY(1,0,buff);
				break;
			
			case Test:
				uart.print_string("!Check the state number!\r\n");//UART tx
				sprintf(buff,"%16s","Test mode");
				lcd.I2C_LCD_write_string_XY(1,0,buff);
				break;
				
			default:
			break;
		}
		
		rx_tag = uart.rx_check();
		
		/*
		distance = sensor.measure_distance();
		sprintf(buff2,"%03d[cm]", distance);
		lcd.I2C_LCD_write_string_XY(1,0,buff2);
		_delay_ms(500);*/
		
		if(sensor_chk)
		{
			read = read_ADC();
			sprintf(buff2,"CdS: %03d",read);
			lcd.I2C_LCD_write_string_XY(1,0,buff2);
		}
		
	}
	return 0;
}

void ADC_init(unsigned char channel)
{
	ADMUX |= (1 <<REFS0);
	
	ADCSRA |= 0x07;
	ADCSRA |= (1<<ADEN);
	ADCSRA |= (1<<ADFR);
	
	ADMUX |= ( (ADMUX & 0xE0) | channel);
	ADCSRA |= (1<<ADSC);
}

int read_ADC(void)
{
	while(!(ADCSRA & (1<<ADIF)));
	return ADC;
}