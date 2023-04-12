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

void uart_init(uint32_t baud);
void uart_send_byte(uint8_t byte);
void uart_send_array(uint8_t *arr, uint16_t len);
void uart_send_string(uint8_t *arr);


uint16_t uart_get_buffer_head(void);
uint8_t uart_read_buffer(void);

#endif /* MY_UART_H_ */