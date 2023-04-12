/*
 * uart.h
 *
 * Created: 4/11/2023 9:20:27 PM
 *  Author: kaili
 */ 


#ifndef MY_UART_H_
#define MY_UART_H_

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define BUFFER_SIZE 128

typedef struct UARTBuffer {
	uint8_t buffer[BUFFER_SIZE];  // buffer of size BUFFER_SIZE initally all zeroes
	uint16_t size;      // the amount of data in the buffer.
	uint16_t head;		// head is the front of the buffer queue. wraps around to
	uint16_t tail;		// tail is incremented and where data is read from.
 } UARTBuffer;

extern UARTBuffer uart_buffer;

void uart_init(uint32_t baud);
void uart_send_byte(uint8_t byte);
void uart_send_array(uint8_t *arr, uint16_t len);
void uart_send_string(uint8_t *arr);


uint16_t uart_get_buffer_size(void);
uint8_t uart_read_buffer(void);

#endif /* MY_UART_H_ */