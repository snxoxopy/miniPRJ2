/* 
* motor.cpp
*
* Created: 2018-09-28 오후 2:22:43
* Author: usuzin
*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "motor.h"

// default constructor
motor::motor()
{
	motor_init();
} //motor

// default destructor
motor::~motor()
{
} //~motor

void motor::motor_init(void)
{
	//타이머
	TCCR1B |= (1 << CS12);	//분주비 256으로 설정
	TCCR1B |= (1 << WGM12);	//Fast PWM mode
	TCCR1A |= ((1 << WGM11) | (1 << WGM10));	//Fast PWM mode
	TCCR1A |= ((1 << COM1A1) | (1 << COM1B1) );

	TCCR3B |= (1 << CS32);	//분주비 256으로 설정
	TCCR3B |= (1 << WGM32);	//Fast PWM mode
	TCCR3A |= (1 << WGM31) | (1 << WGM30);	//Fast PWM mode
	TCCR3A |= ((1 << COM3A1) | (1 << COM3B1) );
	
	LEFT_MOTOR_DDR	|=  ( (1 << LEFT_foward_PIN) | (1 << LEFT_back_PIN) );
	RIGHT_MOTOR_DDR |=	( (1 << RIGHT_forward_PIN) | (1 << RIGHT_back_PIN) );
	
	//LED test
	DDRA |= (1 << PORTA0) | (1 << PORTA1) | (1 << PORTA2) | (1 << PORTA3);
	PORTA = 0x0f;
}

void motor::left_go(int hz)
{
	// F = 1/T
	// freq. 2khz <-> period 0.5ms
	// 속도와 주기는 비례?
	// 분주비 256 -> 16MHz/256 -> 1초에 62500 펄스 발생
	// 1초 62.5k를 1초 2k로 변환
	// OCR이 31250번 펄스가 발생할때 0.5ms
	// OCR의 주파수 = (1초) 1: (펄스개수)16M/256 = x초 : (펄스개수) 31250 (16M/256) * hz
	// x초 = (16M/256)*hz
	// OCR = (16M/256)*hz
	int prd = (16000000/256)*hz;
	ForwardMotor_L();
	SpeedMotor_L(prd);
	_delay_ms(50);
	BackwardMotor_L();
	SpeedMotor_L(prd);
	_delay_ms(50);
}

void motor::right_go()
{
	ForwardMotor_R();
	SpeedMotor_R(50);
	_delay_ms(500);
	BackwardMotor_R();
	SpeedMotor_R(50);
	_delay_ms(500);
}

void motor::stop(void)
{
	PORTB = PORTE = 0x00;
	_delay_ms(500);
};
