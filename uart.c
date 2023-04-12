/*
 * uart.c
 *
 * Created: 4/11/2023 9:19:17 PM
 *  Author: kaili
 */ 
#include "my_uart.h"

#define MAX_BUFFER_SIZE 128
#define F_CPU 16000000

volatile static uint8_t rx_buffer[MAX_BUFFER_SIZE] = {0};	// Initialize as all 0s
volatile static uint16_t buffer_head = 0;
volatile static uint8_t uart_tx_busy = 1;

ISR(USART_RX_vect){
	volatile static uint16_t write_pos = 0;		
	
	rx_buffer[write_pos] = UDR0;			 // read in the UDR0 register 
	buffer_head++;					// declares the size of the queue
	write_pos++;							// increment the position to write new data
	
	if (write_pos >= MAX_BUFFER_SIZE){		// if the rx position overruns the rx max buffer size. return rx pos to 0. "Circular FIFO data structure as stated in the datasheet"
		write_pos = 0; 
	}
	
}

ISR(USART_TX_vect){
	uart_tx_busy = 1;
}

void uart_init(uint32_t baud){
	/*Set baud rate*/
	baud = F_CPU/(16*baud) - 1;
	UBRR0H = (baud & 0x0F00) >> 8;	// mask out the upper 4 bits
	UBRR0L = (baud & 0x00FF);		// mask out the lower 8 bits
	
	/* Enable Rx and Tx as well as Rx and Rx complete interrupts*/
	UCSR0B |= (1<< RXEN0) | (1<<TXEN0) | (1<< RXCIE0) | (1 << TXCIE0);
}


void uart_send_byte(uint8_t data){
	while(uart_tx_busy == 0); // while UART is not transmitting
	
	uart_tx_busy = 0; 
	UDR0 = data;				// load byte passed into the function to the uart buffer
}

void uart_send_array(uint8_t *arr, uint16_t len){
	for(uint16_t i = 0; i < len; ++i){
		uart_send_byte(arr[i]);
	}
}

void uart_send_string(uint8_t *arr) {
	uint16_t i = 0; 
	
	do {
		uart_send_byte(arr[i]);
		i++;
	} while(arr[i] != '\0');
	uart_send_byte(arr[i]);

}

uint16_t uart_get_buffer_head(void){
	return buffer_head;
}

uint8_t uart_read_buffer(void){
	static uint16_t read_pos = 0;
	uint8_t data = rx_buffer[read_pos];		// pull the data out of the buffer at the 
	read_pos++;								
	buffer_head--;							// decrement the head of the list, to point to newest unread data. 
	if(read_pos >= MAX_BUFFER_SIZE){		// reading has gone past the buffers size. move to tail of buffer to extract new data
		read_pos = 0; 
	}
	
	return data;
}
