#ifndef	__UART_H__
#define	__UART_H__

#define	LENGTH_RX0_BUFFER	20
#define	LENGTH_TX0_BUFFER	20

#define BR9600		103
#define BR57600		16
#define BR115200	8

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

class UART0
{
	public:
		UART0();
		~UART0();
		void print_string(char *str);
		void transmit(char data);
		int receive(FILE *stream);
		int	rx_check(void);
	protected:
	private:
		void UART0_init(unsigned int ubrr_baud);
};

#endif
