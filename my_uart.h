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

void uart_init(uint32_t baud);
void uart_send_byte(uint8_t byte);
void uart_send_array(uint8_t *arr, uint16_t len);
void uart_send_string(uint8_t *arr);


uint16_t uart_read_count(void);
uint8_t uart_read(void);

#endif /* MY_UART_H_ */