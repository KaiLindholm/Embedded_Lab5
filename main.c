/*
 * EmbeddedLab5.c
 *
 * Created: 4/11/2023 12:12:04 PM
 * Author : Kai Lindholm & James Ostrowski
 */ 
#define F_CPU 16000000UL

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "my_uart.h"

int main(void) {
	uart_init(9600);
	uint8_t data = 'A';
	sei();
	
    while (1) {
		if(uart_read_count() > 0) {
			data = uart_read();
			uart_send_byte(data);
		}
	}
}
