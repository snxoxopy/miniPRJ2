#include	<avr/io.h>
#include	<avr/interrupt.h>
#include	<stdio.h>
#include	"uart0.h"

volatile unsigned char rx0_buffer[LENGTH_RX0_BUFFER];
volatile unsigned char rx0_head=0, rx0_tail=0;

UART0::UART0()
{
	UART0_init(BR9600);
};
UART0::~UART0(){};

// ���ͷ�Ʈ USART �ʱ�ȭ
void UART0::UART0_init(unsigned int ubrr_baud)
{
	UCSR0B |= 1<<RXEN0 | 1<<TXEN0 | 1<<RXCIE0;
	UBRR0H = 0;
	UBRR0L = ubrr_baud;
}

void UART0::print_string(char *str)	// ���ڿ� �۽�
{
	for(int i = 0; str[i]; i++)			// ��\0�� ���ڸ� ���� ������ �ݺ�
	transmit(str[i]);			// ����Ʈ ���� ���
}

void UART0::transmit(char data)
{
	while( !(UCSR0A & (1 << UDRE0)) );	// �۽� ���� ���
	UDR0 = data;				// ������ ����
}

// ���ͷ�Ʈ�� ���� ���� ���� ȣ��
int UART0::receive(FILE *stream)
{	unsigned char data;
	
	while( rx0_head==rx0_tail );	// ���� ���ڰ� ����

	data = rx0_buffer[rx0_tail];
	rx0_tail = (rx0_tail==LENGTH_RX0_BUFFER-1) ? 0 : rx0_tail + 1;
	
	return data;
}

// USART1 RXC interrupt service
ISR(USART0_RX_vect)
{	
	volatile unsigned char data;
	
	// rx_buffer[] full, ������ ���� ���� ����
	if( (rx0_head+1==rx0_tail) || ((rx0_head==LENGTH_RX0_BUFFER-1) && (rx0_tail==0)) ){
		data = UDR0;
		}else{
		rx0_buffer[rx0_head] = UDR0;
		rx0_head = (rx0_head==LENGTH_RX0_BUFFER-1) ? 0 : rx0_head+1;
	}
}

// USART1 receive char check
int	UART0::rx_check(void)
{
	return (rx0_head != rx0_tail) ? 1 : 0;
}
