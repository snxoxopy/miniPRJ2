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
	int avr_hz = 2*1000;
	char buff[100];
	uart.print_string("chk signal\r\n");
	sprintf(buff,"freq. = %03d[kHz]\r\n", avr_hz/1000);
	uart.print_string(buff);
	
    while (1) 
    {
		//motor 회전
		mtr.left_go(avr_hz);
		//mtr.right_go();
		//mtr.stop();
    }
}

