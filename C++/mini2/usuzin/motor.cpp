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
	TCCR1B |= ( (1 << CS12) | (1 << CS10) );	//오른쪽 바퀴분주비 1024으로 설정?
	TCCR1B |= (1 << WGM12);	//Fast PWM mode
	TCCR1A |= ((1 << WGM11) | (1 << WGM10));	//Fast PWM mode
	TCCR1A |= ((1 << COM1A1) | (1 << COM1B1) );

	TCCR3B |= ( (1 << CS32) | (1 << CS30));		// 왼쪽바퀴 분주비 1024으로 설정
	TCCR3B |= (1 << WGM32);						//Fast PWM mode
	TCCR3A |= (1 << WGM31) | (1 << WGM30);		//Fast PWM mode
	TCCR3A |= ((1 << COM3A1) | (1 << COM3B1) );
	
	LEFT_MOTOR_DDR	|=  ( (1 << LEFT_foward_PIN) | (1 << LEFT_back_PIN) );
	RIGHT_MOTOR_DDR |=	( (1 << RIGHT_forward_PIN) | (1 << RIGHT_back_PIN) );
	
	//LED test
	DDRA |= (1 << PORTA0) | (1 << PORTA1) | (1 << PORTA2) | (1 << PORTA3);

	PORTA = 0x00;
}

void motor::go(int v)
{	
	SpeedMotor_L(v);
	SpeedMotor_R(v);
	
	SpeedMotor_LB(0);
	SpeedMotor_RB(0);
	PORTA = (1 << PORTA0);
}

void motor::T_left(int v)
{
	//int left = v + 200;
	SpeedMotor_L(v);
	SpeedMotor_R(1);
	
	SpeedMotor_LB(0);
	SpeedMotor_RB(0);
	PORTA = (1 << PORTA1);
}

void motor::T_right(int v)
{
	//int right = v + 200;
	SpeedMotor_R(v);
	SpeedMotor_L(1);
	
	SpeedMotor_LB(0);
	SpeedMotor_RB(0);
	PORTA = (1 << PORTA2);
}

void motor::back(int v)
{	
	PORTB = PORTE = 0x00;
	SpeedMotor_L(0);
	SpeedMotor_R(0);
	SpeedMotor_LB(v);
	SpeedMotor_RB(v);
	
	PORTA = (1 << PORTA3);
}

void motor::stop(void)
{
	//PORTB = PORTE = 0x00;
	SpeedMotor_LB(0);
	SpeedMotor_RB(0);
	SpeedMotor_L(0);
	SpeedMotor_R(0);
	PORTA = 0x00;
};
