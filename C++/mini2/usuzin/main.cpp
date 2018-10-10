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


enum{GO=49, T_left, T_right, Stop, Back, Test};//ascii 1 2 3 4 5 6 


int main(void)
{
    UART1 uart;
	motor mtr;
	int mtr_state;
	int mtr_v = 200;	//12ms 동안 high
	int rx_tag = 1;
	char buff[100];
	char prt_state[100];
	
	//bool loop_tag = true;
	bool if_tag = true;
	
	sei();
	
	#if 0
    while(1) 
    {
		if(if_tag)//uart 수신 확인
		{
			if_tag = false;
			//상태 설정 메세지 uart
			uart.print_string("*********************************\r\n");
			uart.print_string("***********Motor_State.**********\r\n");
			uart.print_string("1. Go\r\n");
			uart.print_string("2. Left\r\n");
			uart.print_string("3. Right\r\n");
			uart.print_string("4. Stop\r\n");
			uart.print_string("Select Number>> \r\n");
			
			//mtr_state = 블루투스에서 받아온 결과를 반환
			mtr_state = uart.mtr_chk();
			if(mtr_state)
			{
				sprintf(prt_state,"%s\r\n", ( (mtr_state == 49) ? "-> 1.GO" : (mtr_state == 50 ? "-> 2.Left" : (mtr_state == 51 ? "-> 3.Right" : (mtr_state == 52 ? "-> 4.Stop" : (mtr_state == 53 ? "-> 5.Back" : "") ) ) ) ) );
				//sprintf(buff,"State: %c \r\n", prt_state);
				uart.print_string(prt_state);
			}
			sprintf(buff,"mtr_state = %d\r\n",mtr_state);
			uart.print_string(buff);
		}
		switch(mtr_state)
		{
			case GO:
			mtr.go(mtr_v);
			uart.print_string("GO\r\n");
			break;
			
			case T_left:
			mtr.T_left(mtr_v);
			uart.print_string("T L\r\n");
			break;
			
			case T_right:
			mtr.T_right(mtr_v);
			uart.print_string("T R\r\n");
			break;
			
			case Stop:
			uart.print_string("Stop\r\n");
			mtr.stop();
			break;
			
			case Back:
			mtr.back(mtr_v);
			break;
			
			case Test:
			//rx_tag = 1;
			mtr.go(mtr_v);
			break;
			
			default:
			break;
		}
			
		rx_tag = uart.rx_check();
		
		if( rx_tag == 1 )
		{
			if_tag = true;
		}
		
    }
	#else
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
				uart.print_string("Motor_GO\r\n");//UART tx
				mtr.go(mtr_v);
				break;
				
				case T_left:
				uart.print_string("Motor_Left\r\n");//UART tx
				mtr.T_left(mtr_v);
				break;
				
				case T_right:
				uart.print_string("Motor_right\r\n");//UART tx
				mtr.T_right(mtr_v);
				break;
				
				case Back:
				mtr.back(mtr_v);
				break;
				
				case Stop:
				mtr.stop();
				break;
				
				case Test:
				break;
				
				default:
				break;
			}
			rx_tag = uart.rx_check();
		}
	#endif
	return 0;
}

