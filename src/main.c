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
#include <string.h>
#include <stdlib.h>
#include "i2c/i2c.h"
#include "my_uart.h"
#include "main.h"

void setup(){
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)| (1<<ADEN);
	ADMUX = 0b00000000;   // clear ADMUX for ADC0 pin 
	ADMUX |= (1<<REFS0); // setup internal reference voltage of 1.1V
}

int main(void) {
	setup();
	i2c_init();
	uart_init(9600);
	char str[] = "Started!";
	sei();
	
	uart_send_string(str);
	uart_send_byte('\n');
	
    while (1) {	
		if(uart_string_complete()){
			read_command(uart_get_command());
		}
	}
}

void get_adc_value(){
	ADCSRA |= (1<<ADSC);      // enable a single conversion
	
	while (!(ADCSRA & (1<<ADIF))); // wait for the conversion to be completed		
	
	float result = (ADC*5.0)/1024;	// convert to float 
		
	char buffer[6];	
	dtostrf(result, 3, 2, buffer); // convert float to string 
	
	char header[] = "V = "; 
	uart_send_string(header);
	uart_send_string(buffer);
	uart_send_byte('\n');
		
	ADCSRA |= (1<<ADIF);		// reset AD complete flag for next conversion. 
}

void read_command(char * command) {
	char delim[] = ",";
	char  * token = strtok(command, delim); 
	while(token != NULL){
		uart_send_string(token);
		token = strtok(NULL, delim);
	}
	free(command);
}

