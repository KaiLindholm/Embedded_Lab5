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

	
void setup(){
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)| (1<<ADEN);
	ADMUX = 0b00000000;   // clear ADMUX for ADC0 pin 
	ADMUX |= (1<<REFS0); // setup internal reference voltage of 1.1V
}

int main(void) {
	setup();
	uart_init(9600);
	unsigned char str[] = "Started!\n\r";
	sei();
	
	uart_send_string(str);
	
    while (1) {	
		if(uart_get_buffer_size() > 0){
			uint8_t data = uart_read_buffer();
			if(data == 'G'){
				ADCSRA |= (1<<ADSC);      // enable a single conversion
				while (!(ADCSRA & (1<<ADIF))); // wait for the converstion to be completed 
				
				float result = (ADC*5.0)/1024;
	   			unsigned char buffer[6];
				dtostrf(result, 3, 2, buffer);
				
				unsigned char header[] = "V = ";
				uart_send_string(header);
				uart_send_string(buffer);
				uart_send_byte('\n');
				
				ADCSRA |= (1<<ADIF);
				
				
			}
			//uart_send_byte(data);
		}
	}
}
