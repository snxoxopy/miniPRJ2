/*
 * Motor.cpp
 *
 * Created: 2018-09-28 오후 2:21:44
 * Author : usuzin
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "motor.h"
#include "uart0.h"

int main(void)
{
    UART0 uart; //uart 객체선언
	motor mtr;
	uart.print_string("chk signal\r\n");
	
    while (1) 
    {
		//motor 회전
		mtr.left_go();
		_delay_ms(100);
		mtr.right_go();
		_delay_ms(100);
		mtr.stop();
		_delay_ms(100);
    }
}

