/*
 * EmbeddedLab5.c
 *
 * Created: 4/11/2023 12:12:04 PM
 * Author : Kai Lindholm & James Ostrowski
 */ 
#define F_CPU 16000000

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "my_uart.h"

int main(void) {
	uart_init(9600);
	uint8_t str[] = "Started !!!\n\r";
	sei();
	
	uart_send_string(str);
    while (1) {	
		if(uart_get_buffer_size()>0){
			uint8_t data = uart_read_buffer();
			uart_send_byte(data);
		}
	}
}
