#ifndef	__UART_H__
#define	__UART_H__

/*
 * UART1.h
 *
 * Created: 2018-09-12 오전 11:29:10
 *  Author: usuzin
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

#define	LENGTH_RX_BUFFER	20
#define	LENGTH_TX_BUFFER	20

#define BR9600		103
#define BR57600		16
#define BR115200	8

class UART1
{
	public:
		UART1();
		~UART1();
		void print_string(char *str);
		int send(char data);
		int receive();
		int	rx_check(void);
		int mtr_chk(void);
	protected:
	private:
	void USART1_init(unsigned int ubrr_baud);
};

#endif

