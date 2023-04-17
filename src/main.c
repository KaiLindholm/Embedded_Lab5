/*
 * EmbeddedLab5.c
 *
 * Created: 4/11/2023 12:12:04 PM
 * Author : Kai Lindholm & James Ostrowski
 */ 
#include "config.h"

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

#include "twi_hal.h"
#include "my_uart.h"
#include "main.h"

#define DAC0 0x00
#define DAC1 0x01
#define MAX518 0b01000000

void setup(){
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)| (1<<ADEN);
	ADMUX = 0b00000000;   // clear ADMUX for ADC0 pin 
	ADMUX |= (1<<REFS0); // setup internal reference voltage of 1.1V
}

uint8_t * read_wave_form_file(char * path){
	FILE *fp; 
	
}

int main(void) {
	char str[] = "Started!";
	uint8_t voltage = 0;
	uint32_t speed = 100000;
	uint32_t baud = 9600; 	 
	char * adc; 
	uint8_t err = 0; 
	setup();
	twi_init(speed);
	uart_init(baud);

	voltage = 100;
	uint8_t data[1] = {voltage};
	sei();
	adc = get_adc_value();  // initalize adc for faster computations. 
	
	uart_send_string(str);
	uart_send_byte('\n');	
	err = twi_wire(MAX518, DAC0, data, sizeof(data));
	adc = get_adc_value();
	print_adc_value(adc);
	
	while (1) {	
		if(uart_string_complete()){
			read_command(uart_get_command());
		}
	}
}

char * get_adc_value(){
	ADCSRA |= (1<<ADSC);      // enable a single conversion
	
	while (!(ADCSRA & (1<<ADIF))); // wait for the conversion to be completed		
	
	float result = (ADC*5.0)/1024;	// convert to float 
		
	char * buffer = (char* ) malloc(6 * sizeof(char));	
	dtostrf(result, 3, 2, buffer); // convert float to string 

	ADCSRA |= (1<<ADIF);		// reset AD complete flag for next conversion. 
	
	return buffer; 
}

void print_adc_value(char * buffer){
	char header[] = "V = ";
	uart_send_string(header);
	uart_send_string(buffer);
	uart_send_byte('\n');
	free(buffer); 
}
void read_command(char * command) {
	char delim[] = ",";
	char * token = strtok(command, delim);
	if(strcmp(token, "G") == 0){
		token = strtok(NULL, delim);
		print_adc_value(get_adc_value());
		printf("G\n");
		} else if(strcmp(token, "W") == 0) {
		uint8_t dac = atoi(strtok(NULL, delim));
		uint8_t freq = atoi(strtok(NULL, delim));
		uint8_t cycles = atoi(strtok(NULL, delim));
		gen_wave_form(dac, freq, cycles);
		
		} else if(strcmp(token, "S") == 0) {
			uint8_t dac = atoi(strtok(NULL, delim));
			float voltage = atof(strtok(NULL, delim));
			set_dac_output(dac, voltage);
	}
	
	free(command);
}

void set_adc_value(uint8_t dac, float voltage){
	
}

void gen_wave_form(uint8_t dac, uint8_t freq, uint8_t cycles){
	
}
