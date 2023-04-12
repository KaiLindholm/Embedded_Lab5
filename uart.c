/*
 * uart.c
 *
 * Created: 4/11/2023 9:19:17 PM
 *  Author: kaili
 */ 
#include "my_uart.h"

BUFFER_SIZE


volatile static uint8_t rx_buffer[BUFFER_SIZE];	// Initialize as all 0s
volatile static uint16_t rx_count = 0;
volatile static uint8_t uart_tx_busy = 1;

ISR(USART_RX_vect){
	
	volatile static uint16_t rx_pos = 0; 
	
	rx_buffer[rx_pos] = UDR0;			 // read in the UDR0 register 
	rx_count++; 
	rx_pos++; 
	if (rx_pos >= BUFFER_SIZE){		// if the rx position overruns the rx max buffer size. return rx pos to 0. "Circular FIFO data structure as stated in the datasheet"
		rx_pos = 0; 
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


void uart_send_byte(uint8_t byte){
	while(uart_tx_busy == 0); // while UART is not transmitting
	
	uart_tx_busy = 0; 
	UDR0 = byte;				// load byte passed into the function to the buffer
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
		++i;
	} while(arr[i] != '\0');
	uart_send_byte(arr[i]);

}

uint16_t uart_read_count(void){
	return rx_count;
}

uint8_t uart_read(void){
	static uint16_t rx_pos = 0; 
	uint8_t data = 0; 
	
	data = rx_buffer[rx_pos];
	rx_pos++; 
	rx_count--; 
	if(rx_pos >= BUFFER_SIZE){
		rx_pos = 0; 
	}
	return data;
}
