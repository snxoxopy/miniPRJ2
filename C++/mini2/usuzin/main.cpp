/*
 * usuzin.cpp
 * 수동모드
 * Created: 2018-10-01 오후 4:38:14
 * Author : usuzin
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "motor.h"
#include "UART1.h" //BT 통신을 위해 uart1사용


enum{GO=49, T_left, T_right, Back, Stop, Test};//ascii 1 2 3 4 5 6 


int main(void)
{
    UART1 uart;
	motor mtr;
	int mtr_state;
	int rx_tag = 1;
	char buff[100];
	
	sei();
	
    while (1) 
    {
		//mtr_state = 블루투스에서 받아온 결과를 반환
		if(rx_tag)//rx가 들어오면 mg = 1
		{
			//상태 설정 메세지 uart
			uart.print_string("*********************************\r\n");
			uart.print_string("***********Motor_State.**********\r\n");
			uart.print_string("1. Go\r\n");
			uart.print_string("2. Right\r\n");
			uart.print_string("3. Left\r\n");
			uart.print_string("4. Stop\r\n");
			uart.print_string("Select Number>> \r\n");
			mtr_state = uart.mtr_chk();
			sprintf(buff,"State: %d \r\n", mtr_state);
			uart.print_string(buff);
			rx_tag = 0;
		}
		rx_tag = uart.rx_check();
		switch(mtr_state)
		{
			case GO:
				uart.print_string("Motor_GO\r\n");//UART tx
				mtr.left_go(80);
				mtr.right_go(80);
				break;
			case T_left:
				uart.print_string("Motor_Left\r\n");//UART tx
				mtr.left_go(100);
				mtr.right_go(10);
			case T_right:
				uart.print_string("Motor_right\r\n");//UART tx
				mtr.left_go(10);
				mtr.right_go(100);
			case Back:
				break;
			case Stop:
				mtr.stop();
			case Test:
				uart.print_string("Motor_Stop\r\n");//UART tx
				mtr.left_go(80);
				_delay_ms(500);
				break;
			default:
				break;
		}
    }
}

